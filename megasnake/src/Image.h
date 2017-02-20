#pragma once

#include "itkImage.h"

namespace megasnake {

	using ByteImage = itk::Image<unsigned char, 2>;
	using FloatImage = itk::Image<float, 2>;
	//using RGBImage    = itk::Image<itk::RGBPixel<unsigned char>, 2>;

	class Image
	{
	public:
		Image();
		Image(FloatImage::Pointer _f);

		void setData(FloatImage::Pointer _data);

		void writeToFile(std::string filename) const;

	protected:

		FloatImage::Pointer m_data;
	};



}

