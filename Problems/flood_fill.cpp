#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/flood-fill/

// An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).
// Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, 
// "flood fill" the image.
// To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of 
// the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the
// starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.
// At the end, return the modified image.

// Example 1:
// Input: 
// image = [[1,1,1],[1,1,0],[1,0,1]]
// sr = 1, sc = 1, newColor = 2
// Output: [[2,2,2],[2,2,0],[2,0,1]]
// Explanation: 
// From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected 
// by a path of the same color as the starting pixel are colored with the new color.
// Note the bottom corner is not colored 2, because it is not 4-directionally connected
// to the starting pixel.

// Note:
// The length of image and image[0] will be in the range [1, 50].
// The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
// The value of each color in image[i][j] and newColor will be an integer in [0, 65535].

// Obs: importance of if(oldColor == newColor), attention with the edge case newColor == startColor!!
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
	if(oldColor == newColor) {
		return image;
	}
	image[sr][sc] = newColor;

	vector<pair<int, int>> nextPositions = {{sr+1, sc}, {sr-1, sc}, {sr, sc+1}, {sr, sc-1}};
	for(pair<int, int> p : nextPositions) {
		if(p.first < 0 || p.first >= image.size()) {
			continue;
		}
		if(p.second < 0 || p.second >= image[0].size()) {
			continue;
		}

		if(image[p.first][p.second] == oldColor) {
			floodFill(image, p.first, p.second, newColor);
		}
	}

	return image;
}

int main() {
	vector<vector<int>> image = {{0,0,0},{0,1,1}};
	int sr = 1;
	int sc = 1;
	int newColor = 1;
	printMatrix(floodFill(image, sr, sc, newColor));

	return 0;
}