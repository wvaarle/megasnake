#include "stdafx.h"

#include "Volume.h"

using namespace megasnake;

Volume::Volume()
{
}


Volume::Volume(FloatVolume::Pointer _data) : m_data(_data)
{
}

void megasnake::Volume::setData(FloatVolume::Pointer _data)
{
	m_data = _data;
}

FloatVolume::Pointer Volume::getData() const
{
	return m_data;
}
