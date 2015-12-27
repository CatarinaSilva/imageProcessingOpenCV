#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

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
    cout<<"    cornerRefinementMinAccuracy="<<detectorParams.cornerRefinementMinAccuracy<<endl;
    cout<<"    markerBorderBits="<<detectorParams.markerBorderBits<<endl;
    cout<<"    perspectiveRemovePixelPerCell="<<detectorParams.perspectiveRemovePixelPerCell<<endl;
    cout<<"    perspectiveRemoveIgnoredMarginPerCell="<<detectorParams.perspectiveRemoveIgnoredMarginPerCell<<endl;
    cout<<"    maxErroneousBitsInBorderRate="<<detectorParams.maxErroneousBitsInBorderRate<<endl;
    cout<<"    minOtsuStdDev="<<detectorParams.minOtsuStdDev<<endl;
    cout<<"    errorCorrectionRate="<<detectorParams.errorCorrectionRate<<endl<<endl;
    cout<<"**************************************************"<<endl<<endl;

}

int main(int argc, char *argv[]) {

    aruco::Dictionary dictionary =
        aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(atoi(argv[2])));

    aruco::DetectorParameters detectorParams = aruco::DetectorParameters();

    Mat image = imread(argv[1], 1);
    Mat imageCopy;

    image.copyTo(imageCopy); 
    printParam(detectorParams);

    vector< int > ids;
    vector< vector< Point2f > > corners, rejected;

    // detect markers
    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);

    if(ids.size() > 0) {
       aruco::drawDetectedMarkers(imageCopy, corners, ids, Scalar(100, 255, 0));
    }

    if(rejected.size() > 0) {
       aruco::drawDetectedMarkers(image, rejected, noArray(), Scalar(100, 0, 255));
    }
            
 

    imshow("out", imageCopy);
    waitKey(0);

    return 0;
}


