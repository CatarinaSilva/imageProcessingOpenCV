#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>  
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;
using namespace cv;

struct image_struct{
  char name[256];
};


void printParam(aruco::DetectorParameters detectorParams) {

    cout<<endl;
    cout<<"**************************************************"<<endl<<endl;
    cout<<"  Detector Parameters:  " <<endl<<endl;
    cout<<"**************************************************"<<endl<<endl;
    cout<<"    adaptiveThreshWinSizeMin="<<detectorParams.adaptiveThreshWinSizeMin<<endl;
    cout<<"    adaptiveThreshWinSizeMax="<<detectorParams.adaptiveThreshWinSizeMax<<endl;
    cout<<"    adaptiveThreshWinSizeStep="<<detectorParams.adaptiveThreshWinSizeStep<<endl;
    cout<<"    adaptiveThreshConstant="<<detectorParams.adaptiveThreshConstant<<endl;
    cout<<"    minMarkerPerimeterRate="<<detectorParams.minMarkerPerimeterRate<<endl;
    cout<<"    maxMarkerPerimeterRate="<<detectorParams.maxMarkerPerimeterRate<<endl;
    cout<<"    polygonalApproxAccuracyRate="<<detectorParams.polygonalApproxAccuracyRate<<endl;
    cout<<"    minCornerDistanceRate="<<detectorParams.minCornerDistanceRate<<endl;
    cout<<"    minDistanceToBorder="<<detectorParams.minDistanceToBorder<<endl;
    cout<<"    minMarkerDistanceRate="<<detectorParams.minMarkerDistanceRate<<endl;
    cout<<"    doCornerRefinement="<<detectorParams.doCornerRefinement<<endl;
    cout<<"    cornerRefinementWinSize="<<detectorParams.cornerRefinementWinSize<<endl;
    cout<<"    cornerRefinementMaxIterations="<<detectorParams.cornerRefinementMaxIterations<<endl;
    
    cout<<"    markerBorderBits="<<detectorParams.markerBorderBits<<endl;
    cout<<"    perspectiveRemovePixelPerCell="<<detectorParams.perspectiveRemovePixelPerCell<<endl;
    cout<<"    perspectiveRemoveIgnoredMarginPerCell="<<detectorParams.perspectiveRemoveIgnoredMarginPerCell<<endl;
    cout<<"    maxErroneousBitsInBorderRate="<<detectorParams.maxErroneousBitsInBorderRate<<endl;
    cout<<"    minOtsuStdDev="<<detectorParams.minOtsuStdDev<<endl;
    cout<<"    errorCorrectionRate="<<detectorParams.errorCorrectionRate<<endl<<endl;


}

void printCamMat(Mat cam_matrix) {

    cout<<endl;
    cout<<"*********************************************"<<endl<<endl;
    cout<<"  Camera matrix:  " <<endl<<endl;
    cout<<"*********************************************"<<endl<<endl;
    cout<<cam_matrix<<endl<<endl;

}

void printDistCoeff(Mat dist_coeff) {

    cout<<endl;
    cout<<"*********************************************"<<endl<<endl;
    cout<<"  Distortion coefficients:  " <<endl<<endl;
    cout<<"*********************************************"<<endl<<endl;
    cout<<dist_coeff<<endl<<endl;
   

}

void printRTs(vector<int> ids,  vector< vector< Point2f > > corners, vector<Mat> rvecs, vector<Mat> tvecs, char * origin) {
     
     int i = 0;
     char destination[256];
     char dir[256];
     
     sprintf(dir, "out/info/");
     strcpy(destination, origin );
     
     strcat(destination, ".txt");
     strcat(dir, destination);
     cout<<"  Created "<< dir <<endl;

     ofstream fs(dir);


     while(i < ids.size()){

         Mat rot;
         Mat trans = tvecs[i];

	 Rodrigues(rvecs[i], rot, noArray());
 
         fs<<"*********************************************"<<endl<<endl;
         fs<<"   ID :  "<< ids[i] <<endl<<endl;
         fs<<"*********************************************"<<endl<<endl;

         fs<<"  Rotation:  " <<endl<<endl;
         fs<< rot <<endl<<endl<<endl;

         fs<<"  Translation:  " <<endl<<endl;
         fs<< trans <<endl<<endl<<endl;

         fs<<"  Corners:  " <<endl<<endl;
         fs<<corners[i]<<endl<<endl<<endl;

         i++;

     }

     fs.close();

}


vector< image_struct > getImages(char * dirname){
   vector< image_struct > images;
   DIR *dirp;
   struct dirent *dp;
   int i = 0;

   dirp = opendir(dirname);
   while ((dp = readdir(dirp)) != NULL){
           struct image_struct newElem;
           if(strlen(dp->d_name) >= 5){
              sprintf(newElem.name, "%s", dp->d_name);
              images.push_back(newElem);
           }
   }

   (void) closedir(dirp);
   return images;
}

int main(int argc, char *argv[]) {

    char dirname[10] = "images";
    vector< image_struct > images = getImages(dirname);
    int i = 0;
 
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(atoi(argv[1])));
    aruco::DetectorParameters detectorParams = aruco::DetectorParameters();
	
    printParam(detectorParams);

    strcat(dirname, "/");

    Mat cam_matrix, dist_coeff;
    cam_matrix = (Mat_<float>(3, 3) << 737.596829766027, 0, 317.500934875301, 0, 737.916226174377, 241.563049444188, 0, 0, 1) ;

    printCamMat(cam_matrix);

    dist_coeff = (Mat_<float>(4, 1) << 0.0219781079902679, -0.279709581610154, 0, 0) ;

    printDistCoeff(dist_coeff);
 
    while(i < images.size()){

            char name[256];
            char source[256];
            char destination[256];

            sprintf(destination, "out/images/%s" ,images[i].name);
	    sprintf(name, "%s" ,images[i].name);
            sprintf(source, "%s%s" ,dirname, name);

	    Mat image = imread(source);
	    Mat imageCopy;
            imshow("out",image);
waitKey(0);
            vector<Mat> rvecs, tvecs;

	    image.copyTo(imageCopy); 

	    vector< int > ids;
	    vector< vector< Point2f > > corners, rejected;

	    // detect markers
	    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);

	    if(ids.size() > 0) {
	       aruco::drawDetectedMarkers(imageCopy, corners, ids, Scalar(100, 255, 0));
	    }

	    if(rejected.size() > 0) {
	       aruco::drawDetectedMarkers(imageCopy, rejected, noArray(), Scalar(100, 0, 255));
	    }

	    int a;
	    
	    aruco::estimatePoseSingleMarkers(corners, 0.175, cam_matrix, dist_coeff , rvecs, tvecs);

            for(a=0; a<ids.size(); a++){
               aruco::drawAxis(imageCopy, cam_matrix, dist_coeff, rvecs[a], tvecs[a], 0.200);
            }

            imwrite( destination, imageCopy );
            printRTs(ids, corners, rvecs, tvecs, name);

            i++;
    }


    return 0;
}


