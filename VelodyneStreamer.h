#ifndef VELODYNESTREAMER_H
#define VELODYNESTREAMER_H

#include <list>
#include <vector>

#include <pcl/common/common_headers.h>

#include "VCloud.h"
#include "PcapReader.h"
#include "TauronTypes.h"


enum SensorType { HDL64, HDL32, VLP16 };

class VelodyneStreamer {
private:
	void parseAzimuth(const unsigned char* data, int& azimuth);
	void parseDataBlock(const unsigned char* data, int& distance, int& intensity);

	int interpolate_azimuth(int previous_azimuth, int next_azimuth);

	bool nextFrameVLP16(VCloud& cloud);
	bool nextFrameVLP16DD(VCloud& cloud);
	bool nextFrameHDL32(VCloud& cloud);
	bool nextFrameHDL64(VCloud& cloud);

	bool nextFrameVLP16(pcl::PointCloud<pcl::PointXYZI>& cloud);
	bool nextFrameVLP16(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  bool nextFrameVLP16(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, std::vector<TData>& data);
	bool nextFrameVLP16DD(pcl::PointCloud<pcl::PointXYZI>& cloud);
	bool nextFrameVLP16DD(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  bool nextFrameVLP16DD(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, std::vector<TData>& data);
	bool nextFrameHDL32(pcl::PointCloud<pcl::PointXYZI>& cloud);
	bool nextFrameHDL32(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  bool nextFrameHDL32(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, std::vector<TData>& data);
	bool nextFrameHDL64(pcl::PointCloud<pcl::PointXYZI>& cloud);
	bool nextFrameHDL64(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  bool nextFrameHDL64(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, std::vector<TData>& data);

protected:
	PcapReader _reader;

public:
	VelodyneStreamer() = default;
	VelodyneStreamer(std::string pcap);
	~VelodyneStreamer();

	SensorType sensor;
	bool dual_distance_return;

	bool open(std::string pcap);

	bool nextFrame(VCloud& cloud);
	bool nextFrame(pcl::PointCloud<pcl::PointXYZI>& cloud);
	bool nextFrame(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  bool nextFrame(pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud, std::vector<TData>& data);
	bool nextFrameParallel(VCloud& cloud);

  bool nextFrameInOrder(std::vector<std::vector<VPoint>>& pointlist);
  bool nextFrameInOrder64(std::vector<std::vector<VPoint>>& pointlist);

	std::vector<int> HDL_laser_arrangements();
};

#endif