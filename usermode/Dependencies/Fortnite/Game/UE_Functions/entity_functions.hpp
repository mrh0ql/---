#include "../../../../Includes/includes.hpp"
#include "../UE_Defnitions/entity_engine.hpp"
#include "../UE_Defnitions/entity_enums.hpp"
#include "../../../../Includes/Definitions/c_definitions.hpp"
#include "../../../../Includes/Definitions/hex_definitions.hpp"
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>



fvector location;
frotator rotation;
float fov;

struct
{
	double a;
	double b;
	double c;

} rotation_s;

uintptr_t bone_;

ftransform comp_;

std::vector<std::pair<int, int>> bone_pairs =
{
 {110, 66},
	{66, 9},
		{66, 38},
			{9, 10},
				{38, 39},
						{10, 11},
								{39, 40},
						{66, 2},
					{2, 78},
				{2, 71},
			{78, 79},
		{79, 82},
	{71, 72},
 {72, 75}
};

namespace Game_ {

	class World_ {
	public:
		void get_bone_array(uintptr_t);

		fvector get_bone(int);

		std::unordered_map<int, fvector> get_skeleton(const std::vector<std::pair<int, int>>& bone_pairs);
	};

	class Camera_ {
	public:

		fvector2d w2s(fvector);

		void get_camera();
	};

}
inline Game_::World_ bone_manager;
inline Game_::Camera_ camera_manager;



void Game_::World_::get_bone_array(uintptr_t ent) {

	bone_ = device_().read <uintptr_t>(ent + 0x5F0 + (device_().read <int>(ent + 0x638) * 0x10));

	comp_ = device_().read<ftransform>(ent + 0x1E0);
}

fvector Game_::World_::get_bone(int id) {

	auto bone = device_().read<FTransform>(bone_ + id * 0x60);

	D3DMATRIX bone_matrix = MatrixMultiplication(bone.ToMatrixWithScale(), comp_.ToMatrixWithScale());

	return fvector(bone_matrix._41, bone_matrix._42, bone_matrix._43);
}

std::unordered_map<int, fvector> Game_::World_::get_skeleton(const std::vector<std::pair<int, int>>& bone_pairs) {
	std::unordered_map<int, fvector> bone_positions;
	bone_positions.reserve(bone_pairs.size() * 2);

	D3DMATRIX comp2world = comp_.ToMatrixWithScale();

	for (const auto& pair : bone_pairs) {
		for (int id : {pair.first, pair.second}) {
			auto result = bone_positions.emplace(id, fvector{});
			if (result.second) {
				FTransform bone = device_().read<FTransform>(bone_ + (id * 0x60));
				D3DMATRIX bonematrix = bone.ToMatrixWithScale();
				D3DMATRIX matrix = MatrixMultiplication(bonematrix, comp2world);
				result.first->second = fvector(matrix._41, matrix._42, matrix._43);
			}
		}
	}

	return bone_positions;
}

void Game_::Camera_::get_camera() {

	auto& cache = GameCache::Cache::getInstance();

	fov = device_().read<float>(cache.get_pcontroller().value_or(0) + 0x3B4) * 90.f;

	rotation_s.a = device_().read<double>(cache.get_rotation_ptr().value_or(0));
	rotation_s.b = device_().read<double>(cache.get_rotation_ptr().value_or(0) + 0x20);
	rotation_s.c = device_().read<double>(cache.get_rotation_ptr().value_or(0) + 0x1d0);

	location = device_().read<fvector>(cache.get_location_ptr().value_or(0));
	rotation.Pitch = asin(rotation_s.c) * (180.0 / M_PI);
	rotation.Yaw = (atan2f(rotation_s.a * -1, rotation_s.b) * (180.0 / M_PI)) * -1 * -1;
	rotation.Roll = 0.0;
}

auto in_screen(fvector2d screen_location) -> bool {

	if (screen_location.x > 0 && screen_location.x < C_Overlay::c_screen_width && screen_location.y > 0 && screen_location.y < C_Overlay::c_screen_height) return true;
	else return false;
}


fvector2d Game_::Camera_::w2s(fvector worldlocation) {

	camera_manager.get_camera();

	_MATRIX tempMatrix = Matrix1(rotation);

	fvector vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	fvector vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	fvector vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	fvector vDelta = worldlocation - location;
	fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	return fvector2d((C_Overlay::c_screen_width / 2.0f) + vTransformed.x * (((C_Overlay::c_screen_width / 2.0f) / tanf(fov * (float)M_PI / 360.f))) / vTransformed.z, (C_Overlay::c_screen_height / 2.0f) - vTransformed.y * (((C_Overlay::c_screen_width / 2.0f) / tanf(fov * (float)M_PI / 360.f))) / vTransformed.z);
}