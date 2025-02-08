#include <iostream>
#include <vector>
/*rotate an image in the form of 4-channel rgba image*/

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
      for (int j = 0; j < num_channels; j++) {
        // Flips the width and height and indexes into the correct pixel in the rotated image to set the channel
        rotated[((width - c - 1) * height * num_channels) + (r * num_channels) + j] = 
            input[(r * width * num_channels) + (c * num_channels) + j];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
