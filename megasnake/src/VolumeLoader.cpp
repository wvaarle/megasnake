#include "stdafx.h"

#include <filesystem>

#include "itkBMPImageIO.h"
#include "itkImageSeriesReader.h"
#include "itkRescaleIntensityImageFilter.h"

#include "VolumeLoader.h"

using namespace megasnake;

std::vector<std::string> getImageFiles(stdfs::path path)
{
	std::vector<std::string> filenames;
	const stdfs::directory_iterator end{};
	for (stdfs::directory_iterator iter{ path }; iter != end; ++iter) {
		if (stdfs::is_regular_file(*iter))
			filenames.push_back(iter->path().string());
	}
	return filenames;
}

VolumeLoader::VolumeLoader()
{
}

std::shared_ptr<Volume> VolumeLoader::load(stdfs::path path)
{
	using ReaderType = itk::ImageSeriesReader<FloatVolume>;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetImageIO(itk::BMPImageIO::New());
	reader->SetFileNames(getImageFiles(path));

	try	{
		reader->Update();
	}
	catch (itk::ExceptionObject & e) {
		std::cerr << e << std::endl;
		return nullptr;
	}

	using RescaleFilter = itk::RescaleIntensityImageFilter<FloatVolume, FloatVolume>;
	auto rescaleFilter = RescaleFilter::New();
	rescaleFilter->SetInput(reader->GetOutput());
	rescaleFilter->SetOutputMinimum(0.f);
	rescaleFilter->SetOutputMaximum(1.f);
	rescaleFilter->Update();

	return std::make_shared<Volume>(rescaleFilter->GetOutput());
}
