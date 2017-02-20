#pragma once

#include "Image.h"
#include "Volume.h"

namespace megasnake {

	enum class SliceDirection { X, Y, Z	};

	class View
	{
	public:
		View(std::shared_ptr<Volume> volume);

		std::shared_ptr<Volume> getVolume() const;
		void setVolume(std::shared_ptr<Volume> volume);

		std::shared_ptr<Image> getImage() const;
		
		void setSliceDirection(SliceDirection direction);
		SliceDirection getSliceDirection() const;

		std::pair<int, int> getRange() const;

		void setSliceNumber(int slicenumber);
		int getSliceNumber() const;

	private:
		
		void updateSlice();

		SliceDirection m_direction;
		int m_slicenumber;

		std::shared_ptr<Volume> m_volume;
		std::shared_ptr<Image> m_image;

	};

}
