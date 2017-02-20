#pragma once

#include "itkImage.h"

namespace megasnake {

	//using ByteVolume  = itk::Image<unsigned char, 3>;
	using FloatVolume = itk::Image<float, 3>;

	class Volume
	{
	public:
		Volume();
		Volume(FloatVolume::Pointer _f);

		void setData(FloatVolume::Pointer _data);
		FloatVolume::Pointer getData() const;

	protected:

		FloatVolume::Pointer m_data;
	};



}
