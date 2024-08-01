#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/features2d/features2d.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int main(int argc, char **argv){
    if (argc != 3){
        cout << "usage: feature_extraction img1 img 2" << endl;
        return 1;
    }

    Mat img_1 = imread(argv[1], IMREAD_COLOR);
    Mat img_2 = imread(argv[2], IMREAD_COLOR);
    assert(img_1.data !=nullptr && img_2.data !=nullptr);

    std::vector<KeyPoint> keypoint1, keypoint2;
    Mat descriptors1, descriptors2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    detector->detect(img_1, keypoint1);
    detector->detect(img_2, keypoint2);

    descriptor->compute(img_1, keypoint1, descriptors1);
    descriptor->compute(img_2, keypoint2, descriptors2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "extract ORB cost = " << time_used.count() << "seconds." << endl;

    Mat outimg1;
    drawKeypoints(img_1, keypoint1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("ORB features", outimg1);

    vector<DMatch> matches;
    t1 = chrono::steady_clock::now();
    matcher->match(descriptors1, descriptors2, matches);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "match ORB cost = " << time_used.count() << "seconds." << endl;

    auto min_max = minmax_element(matches.begin(), matches.end(), [](const DMatch &m1, const DMatch &m2) { return m1.distance < m2.distance;});
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;

    printf("--Max dist : %f \n", max_dist);
    printf("--Min dist : %f \n", min_dist);


    std::vector<DMatch> good_matches;
    std::vector<KeyPoint> good_keypoint1, good_keypoint2;

    for (int i = 0; i < descriptors1.rows; i++){
        if (matches[i].distance <= max(min_dist, 30.0)){
            good_matches.push_back(matches[i]);
            good_keypoint1.push_back(keypoint1[i]);
        }
    }

    Mat img_match;
    Mat img_goodmatch;

    drawMatches(img_1, keypoint1, img_2, keypoint2, matches, img_match);
    drawMatches(img_1, keypoint1, img_2, keypoint2, good_matches, img_goodmatch);

    imshow("all matches", img_match);
    imshow("good matches", img_goodmatch);
    waitKey(0);

    return 0;


}

