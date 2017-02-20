#include "stdafx.h"

#include "View.h"

#include "itkExtractImageFilter.h"

using namespace megasnake;

View::View(std::shared_ptr<Volume> volume) : m_volume(volume)
{
	m_direction = SliceDirection::Z;
	m_slicenumber = 0;
	updateSlice();
}

std::shared_ptr<Volume> View::getVolume() const
{
	return m_volume;
}

void View::setVolume(std::shared_ptr<Volume> volume)
{
	m_volume = volume;
}

void View::setSliceDirection(SliceDirection direction)
{
	m_direction = direction;
	m_slicenumber = 0;
	updateSlice();
}

SliceDirection View::getSliceDirection() const
{
	return m_direction;
}

void View::setSliceNumber(int slicenumber)
{
	m_slicenumber = slicenumber;
	updateSlice();
}

int View::getSliceNumber() const
{
	return m_slicenumber;
}

std::shared_ptr<Image> View::getImage() const
{
	return m_image;
}

std::pair<int, int> View::getRange() const
{
	auto size = m_volume->getData()->GetLargestPossibleRegion().GetSize();
	switch (m_direction) {
		case SliceDirection::X: return std::pair<int, int>(0, size[0]);
		case SliceDirection::Y: return std::pair<int, int>(0, size[1]);
		case SliceDirection::Z: return std::pair<int, int>(0, size[2]);
		default:                return std::pair<int, int>(0, 0);
	}
}

void View::updateSlice()
{
	auto volumesize = m_volume->getData()->GetLargestPossibleRegion().GetSize();
	FloatVolume::IndexType index = { 0,0,0 };

	using ExtractFilterType = itk::ExtractImageFilter<FloatVolume, FloatImage>;
	ExtractFilterType::Pointer extractor = ExtractFilterType::New();
	extractor->SetDirectionCollapseToSubmatrix();

	FloatVolume::RegionType desiredRegion;
	switch (m_direction) {
		case SliceDirection::X: 
			index[0] = m_slicenumber;
			volumesize[0] = 0;
			break;
		case SliceDirection::Y: 
			index[1] = m_slicenumber;
			volumesize[1] = 0;
			break;
		case SliceDirection::Z: 
			index[2] = m_slicenumber;
			volumesize[2] = 0;
			break;
	}
	desiredRegion.SetSize(volumesize);
	desiredRegion.SetIndex(index);
	extractor->SetExtractionRegion(desiredRegion);
	extractor->SetInput(m_volume->getData());

	try {
		extractor->Update();
	}
	catch (itk::ExceptionObject & e) {
		std::cerr << e << std::endl;
		return;
	}

	m_image = std::make_shared<Image>(extractor->GetOutput());
}
