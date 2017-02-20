#include "stdafx.h"

#include "itkImageFileWriter.h"
#include "itkTIFFImageIO.h"

#include "Image.h"

using namespace megasnake;

Image::Image()
{
}

Image::Image(FloatImage::Pointer _data) : m_data(_data)
{
}

void Image::setData(FloatImage::Pointer _data)
{
	m_data = _data;
}

void Image::writeToFile(std::string filename) const
{
	using WriterType = itk::ImageFileWriter<FloatImage>;
	WriterType::Pointer writer = WriterType::New();
	writer->SetImageIO(itk::TIFFImageIO::New());
	writer->SetFileName(filename);
	writer->SetInput(m_data);
	try {
		writer->Update();
	}
	catch (itk::ExceptionObject & e) {
		std::cerr << e << std::endl;
	}
}
