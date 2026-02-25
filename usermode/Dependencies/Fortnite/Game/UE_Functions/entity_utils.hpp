#include "entity_functions.hpp"
#include "../../../UI/Framework/Drawing.hpp"
#include <thread>
#include "../../../../Includes/includes.hpp"

struct weapon_info_
{
	std::string weapon_name;
};

std::string local_player_weapon;
weapon_info_ weapon_info;


class Environment_ {
public:

	class drawing_ {
	public:

		void render_elements( );
	};

	class Weapons_ {
	public:

		weapon_info_ get_weapon_name( uint64_t );
	};

	class PState_ {
	public:

		bool is_visible( uintptr_t );

		std::string get_platform( uintptr_t );

		std::string get_player_name( uintptr_t  );


		ImVec4 get_rank_color(int32_t);

		std::string get_rank(int32_t);
	};

}; 	



ImVec4 Environment_::PState_::get_rank_color( int32_t Tier )
{
	if ( Tier == 0 || Tier == 1 || Tier == 2 )
		return ImVec4( 0.902f, 0.580f, 0.227f, 1.0f ); // Bronze
	else if ( Tier == 3 || Tier == 4 || Tier == 5 )
		return ImVec4( 0.843f, 0.843f, 0.843f, 1.0f ); // Silver
	else if ( Tier == 6 || Tier == 7 || Tier == 8 )
		return ImVec4( 1.0f, 0.871f, 0.0f, 1.0f ); // Gold
	else if ( Tier == 9 || Tier == 10 || Tier == 11 )
		return ImVec4( 0.0f, 0.7f, 0.7f, 1.0f ); // Platinum
	else if ( Tier == 12 || Tier == 13 || Tier == 14 )
		return ImVec4( 0.0f, 0.0f, 0.7f, 1.0f ); // Diamond
	else if ( Tier == 15 )
		return ImVec4( 0.7f, 0.7f, 0.7f, 1.0f ); // Elite
	else if ( Tier == 16 )
		return ImVec4( 1.0f, 0.6f, 0.0f, 1.0f ); // Champion
	else if ( Tier == 17 )
		return ImVec4( 0.6f, 0.0f, 0.6f, 1.0f ); // Unreal
	else
		return ImVec4( 1.0f, 1.0f, 1.0f, 1.0f ); // Unranked
}

std::string Environment_::PState_::get_rank( int32_t Tier )
{
	if ( Tier == 0 )
		return std::string( "Bronze 1" );
	else if ( Tier == 1 )
		return std::string( "Bronze 2" );
	else if ( Tier == 2 )
		return std::string( "Bronze 3" );
	else if ( Tier == 3 )
		return std::string( "Silver 1" );
	else if ( Tier == 4 )
		return std::string( "Silver 2" );
	else if ( Tier == 5 )
		return std::string( "Silver 3" );
	else if ( Tier == 6 )
		return std::string( "Gold 1" );
	else if ( Tier == 7 )
		return std::string( "Gold 2" );
	else if ( Tier == 8 )
		return std::string( "Gold 3" );
	else if ( Tier == 9 )
		return std::string( "Platinum 1" );
	else if ( Tier == 10 )
		return std::string( "Platinum 2" );
	else if ( Tier == 11 )
		return std::string( "Platinum 3" );
	else if ( Tier == 12 )
		return std::string( "Diamond 1" );
	else if ( Tier == 13 )
		return std::string( "Diamond 2" );
	else if ( Tier == 14 )
		return std::string( "Diamond 3" );
	else if ( Tier == 15 )
		return std::string( "Elite" );
	else if ( Tier == 16 )
		return std::string( "Champion" );
	else if ( Tier == 17 )
		return std::string( "Unreal" );
	else
		return std::string( "Unranked" );
}

weapon_info_ Environment_::Weapons_::get_weapon_name( uint64_t actor ) {

	uintptr_t current_weapon = device_( ).read<uintptr_t>( actor + offset_()->get_apply_offsets( ).CurrentWeapon( ) );

	uint64_t weapon_data = device_( ).read<uint64_t>( current_weapon + offset_()->get_apply_offsets( ).WeaponData( ) );
	if ( !weapon_data ) return { };

	uint64_t fname_text = device_( ).read<uint64_t>( weapon_data + 0xB0 );
	if ( !fname_text ) return { };

	uint32_t name_length = device_( ).read<uint32_t>( fname_text + 0x30 );
	if ( !name_length ) return { };

	wchar_t* WeaponName = new wchar_t[uint64_t( name_length ) + 1];

	device_( ).read1( ( device_( ).read<PVOID>( fname_text + 0x28 ) ),
		WeaponName,
		name_length * sizeof( wchar_t ) );

	std::wstring wWeaponName( WeaponName );
	delete[] WeaponName;

	weapon_info_ weapon_info;
	weapon_info.weapon_name = std::string( wWeaponName.begin( ), wWeaponName.end( ) );
	return weapon_info;
}
std::string Environment_::PState_::get_platform( uintptr_t ps ) {

	uintptr_t test_platform = device_( ).read<uintptr_t>( ps + 0x440);

	wchar_t platform[64] = { 0 };

	device_( ).read_array( ( test_platform ),
		reinterpret_cast<uint8_t*>( platform ),
		sizeof( platform ) );

	std::wstring platform_wstr( platform );

	std::string platform_str( platform_wstr.begin( ), platform_wstr.end( ) );

	return platform_str;
}

bool Environment_::PState_::is_visible( uintptr_t skeletal_mesh ) {

	auto& cache = GameCache::Cache::getInstance();
	auto world_time = device_().read<double>(cache.get_uworld().value_or(0) + 0x198);
	auto last_render = device_().read<float>(skeletal_mesh + 0x328);
	return (bool)(last_render + 0.06f >= world_time);
}


std::string Environment_::PState_::get_player_name(uintptr_t player_state)
{
	int pNameLength;
	_WORD* pNameBufferPointer;
	int i;
	char v25;
	int v26;
	int v29;

	wchar_t* pNameBuffer;

	uintptr_t pNameStructure = device_().read<uintptr_t>(player_state + 0xA08); //pNameStructure
	if (device_().IsValidAddress_(pNameStructure)) {
		pNameLength = device_().read<int>(pNameStructure + 0x10);
		if (pNameLength <= 0)
			return "BOT";

		pNameBuffer = new wchar_t[pNameLength];
		uintptr_t pNameEncryptedBuffer = device_().read <uintptr_t>(pNameStructure + 0x8);
		if (device_().IsValidAddress_(pNameEncryptedBuffer)) {
			device_().read_large_array(pNameEncryptedBuffer, pNameBuffer, pNameLength);

			v25 = pNameLength - 1;
			v26 = 0;
			pNameBufferPointer = (_WORD*)pNameBuffer;

			for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7) {
				v29 = pNameLength - 1;
				if (!(_DWORD)pNameLength)
					v29 = 0;

				if (v26 >= v29)
					break;

				i += 3;
				++v26;
			}

			std::wstring temp_wstring(pNameBuffer);
			delete[] pNameBuffer;
			return std::string(temp_wstring.begin(), temp_wstring.end());
		}

		delete[] pNameBuffer;
	}
}



void Environment_::drawing_::render_elements( )
{
	ImU32 col1 = ImGui::GetColorU32(ImVec4(46,139,87, 1.0f));
	ImU32 col2 = ImGui::GetColorU32(ImVec4(0.1373f, 0.4784f, 0.3412f, 1.0f));

	outlined_text( ImGui::GetBackgroundDrawList( ), 5, 13, col1, "Immortal" );

	outlined_text( ImGui::GetBackgroundDrawList( ), 60, 13, col2, " Public" );

	if ( C_Misc::c_show_fps )
	{
		char fppss [256 ];

		outlined_text( ImGui::GetBackgroundDrawList( ), 5, 27, ImColor( 255, 255, 255, 255 ), "frame" );

		sprintf_s( fppss, std::string( "rate %.1f FPS" ).c_str( ), ImGui::GetIO( ).Framerate );

		outlined_text( ImGui::GetBackgroundDrawList( ), 42, 27, ImColor( 255, 0, 0, 255 ), fppss );
	}

}
inline Environment_::Weapons_ weapon_manager;
inline Environment_::PState_ player_manager;
inline Environment_::drawing_ utilites_manager;





















































































std::wstring string_to_wstring(const std::string& str) {
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
	return wstr;
}

std::string wstring_to_utf8(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
	return str;
}

bool has_clicked;

std::chrono::steady_clock::time_point tb_begin;

std::chrono::steady_clock::time_point tb_end;

int tb_time_since;

__int64 TargetedBuild;

bool bTargetedBuild;

uintptr_t TargetedFortpawn;

int HeldWeaponType;

HWND hwndd = NULL;


