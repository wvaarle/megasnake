#pragma once

#include <experimental/filesystem>
#include <memory>

#include "Volume.h"

namespace stdfs = std::experimental::filesystem;

namespace megasnake {

	class VolumeLoader
	{
	public:
		VolumeLoader();

		std::shared_ptr<Volume> load(stdfs::path filename);

	private:


	};

}