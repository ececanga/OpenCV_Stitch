/**
 * Title: OpenCV Image Processing
 * Author: Ece ÇANGA
 * Date: August-September 2019
 * Description: OpenCV Video Stitching program based on stitching frames.
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main() {

	cout << "Camera Player" << endl;
	/*
	---------------------------------------------- FOR TESTING THE INPUT VIDEO ----------------------------------------------
	VideoCapture vCap3("InputVideo2.mp4");
	Mat testFrame;
	for (;;) {
		vCap3 >> testFrame;
		imshow("Test frame", testFrame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25);
		if (c == 27)
		break;
	}
	vCap3.release();
	--------------------------------------------------------------------------------------------------------------------------
	*/



	// Create a VideoCapture object and open the input file
	VideoCapture vCap("InputVideo1.mp4");
	VideoCapture vCap1("InputVideo2.mp4");

	// If the input is the web camera, pass 0 instead of the video file name
	// PS: VideoCapture objects with the camera inputs given cause runtime exception.
	// To handle such exception, disable stitching. (This program runs on CPU, GPU usage is required for real-time processing.)
	//VideoCapture vCap(0);
	//VideoCapture vCap1(1);

	// Check if cameras are opened successfully.
	if (!vCap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	if (!vCap1.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -2;
	}

	while (1) {

		Mat frame, frame1, finalFrame;

		// Capture frame-by-frame
		vCap >> frame;
		vCap1 >> frame1;

		// If the frame is empty, break immediately
		if (frame.empty()) {
			cout << "Frame is empty" << endl;
			return -3;
			break;
		}
		if (frame1.empty()) {
			cout << "Frame1 is empty" << endl;
			return -4;
			break;
		}

		// Display the resulting frame
		imshow("First frame", frame);
		imshow("Second frame", frame1);

		// Push each frame one by one into the final vector 
		vector<Mat> finalFrameImages;


		// Resizing frames in order to get proper output.
		//frame.resize(CAP_PROP_FRAME_WIDTH, 640);
		//frame.resize(CAP_PROP_FRAME_HEIGHT, 480);
		//frame1.resize(CAP_PROP_FRAME_WIDTH, 640);
		//frame1.resize(CAP_PROP_FRAME_HEIGHT, 480);

		// Pushing the frames into the final container that are obtained from input one by one.
		finalFrameImages.push_back(frame);
		finalFrameImages.push_back(frame1);

		// Stitching all frames that are stored the final frame images vector set
		Stitcher::Mode mode = Stitcher::PANORAMA;
		Ptr<Stitcher> stitcher = Stitcher::create(mode);
		Stitcher::Status status = stitcher->stitch(finalFrameImages, finalFrame);

		if (status != Stitcher::OK) {
			cout << "Can't stitch images" << endl;
			return status;
		}

		// Saving video image if necessary
		//cv::VideoWriter::write(finalFrame);
		//imwrite("Final frame", finalFrame);


		// Displaying the stitched result frame
		imshow("Resulting frame", finalFrame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(10); // Updated from 25 to 1
		if (c == 27) // ASCII value to exit (ESC in this case)
			break;
	}

	// When everything done, release the video capture object
	vCap.release();
	vCap1.release();

	// Closes all the frames
	destroyAllWindows();

	cout << "DONE" << endl;
	return 0;
}