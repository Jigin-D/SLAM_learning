#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

int main() {
    
    VideoCapture cap(4, cv::CAP_V4L2);
    if (!cap.isOpened()) {
        cout << "Error: Could not open camera" << endl;
        return -1;
    }

    
    namedWindow("Camera", WINDOW_AUTOSIZE);

    Mat frame;
    int m = 1;
    
    while (m <= 2)
    {
        bool success = cap.read(frame);

        if (!success) {
            cout << "Error: Could not read frame from camera" << endl;
            break; 
        }

        imshow("Camera", frame);

        char key = waitKey(1);

        if (key == 'q'){
            break;
        }else if (key == 's'){
            string filename = "img_" + to_string(m) + ".png";
            imwrite(filename, frame);
            cout << "saved!" << endl;
            m = m + 1;
        }

        
    }
    

    
   
    cap.release();
    destroyAllWindows();

    int result = system("./triangulation img_1.png img_2.png");

    return 0;

}
