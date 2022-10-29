#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include <stdint.h>

#include <string>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <cerrno>

// time stuff
#include <ctime>
#include <time.h>
#include <iomanip>

// OpenGL and graphics stuff 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// fonts
#include <ft2build.h>
#include <freetype/freetype.h>


// logging setting
#define MEM_LOGGING_ACTIVE	1
#define MEM_LOG_TO_FILE		0

// constants
#define PI		3.1415926f
#define TWO_PI	2.0f * PI
#define E		2.7182818f

// ------------------------------------ LOGGING

#define MEM_RESET		"\033[0m"
#define MEM_BLACK		"\033[30m"			   /*  Black			*/
#define MEM_RED			"\033[31m"			   /*  Red				*/
#define MEM_GREEN		"\033[32m"			   /*  Green			*/
#define MEM_YELLOW		"\033[33m"			   /*  Yellow			*/
#define MEM_BLUE		"\033[34m"			   /*  Blue				*/
#define MEM_MAGENTA		"\033[35m"			   /*  Magenta			*/
#define MEM_CYAN		"\033[36m"			   /*  Cyan				*/
#define MEM_WHITE		"\033[37m"			   /*  White			*/
#define MEM_BOLDBLACK   "\033[1m\033[30m"      /*  Bold Black		*/
#define MEM_BOLDRED     "\033[1m\033[31m"      /*  Bold Red			*/
#define MEM_BOLDGREEN   "\033[1m\033[32m"      /*  Bold Green		*/
#define MEM_BOLDYELLOW  "\033[1m\033[33m"      /*  Bold Yellow		*/
#define MEM_BOLDBLUE    "\033[1m\033[34m"      /*  Bold Blue		*/
#define MEM_BOLDMAGENTA "\033[1m\033[35m"      /*  Bold Magenta		*/
#define MEM_BOLDCYAN    "\033[1m\033[36m"      /*  Bold Cyan		*/
#define MEM_BOLDWHITE   "\033[1m\033[37m"      /*  Bold White		*/

namespace mem
{
	class FileLogger
	{
	public:
		FileLogger() = default;

		// path to folder
		FileLogger(const std::string& filePath)
		{
			m_Log = std::ofstream(filePath + "/Log.txt");
		}

		~FileLogger()
		{
			m_Log.close();
		}

		void Print()
		{
			m_Log << "\n";
		}

		template <typename T>
		void Print(const T& x)
		{
			m_Log << x << "\n";
		}

		template <typename T>
		void Printnr(const T& x)
		{
			m_Log << x;
		}

		void Print(const glm::vec2& v)
		{
			std::cout << "X: " << v.x << ", " << "Y: " << v.y << "\n";
		}

		void Print(const glm::vec3& v)
		{
			std::cout << "X: " << v.x << ", " << "Y: " << v.y << ", " << "Z: " << v.z << "\n";
		}

		void Print(const glm::vec4& v)
		{
			std::cout << "R: " << v.r << ", " << "G: " << v.g << ", " << "B: " << v.b << ", " << "A: " << v.a << "\n";
		}

		template <typename T>
		void Print(const std::vector<T>& v)
		{
			Printnr("{ ");
			for (T obj : v)
			{
				Printnr(obj);
				Printnr(", ");
			}
			Printnr(" }");
		}

		void PrintCurrentTime()
		{
			struct tm buf;
			time_t now = time(0);
			localtime_s(&buf, &now);
			m_Log << std::put_time(&buf, "(%Y-%m-%d %X)");
		}

		void StartLine()
		{
			m_Log << m_LineCount << " ";
			m_LineCount++;
		}

	private:
		std::ofstream m_Log;
		uint32_t m_LineCount = 0;
	};
}

#if MEM_LOGGING_ACTIVE
	#if MEM_LOG_TO_FILE
		static mem::FileLogger fLogger("../../OpenGL 2D Engine");
		#define LOG(x) fLogger.StartLine(); fLogger.Print(x)
		#define INFO(x) fLogger.StartLine(); fLogger.PrintCurrentTime(); fLogger.Printnr(" INFO: "); fLogger.Print(x)
		#define WARNING(x) fLogger.StartLine(); fLogger.PrintCurrentTime(); fLogger.Printnr(" WARNING: "); fLogger.Print(x)
		#define ERROR(x) fLogger.StartLine(); fLogger.PrintCurrentTime(); fLogger.Printnr(" ERROR: "); fLogger.Print(x)
		#define FATAL(x) fLogger.StartLine(); fLogger.PrintCurrentTime(); fLogger.Printnr(" FATAL ERROR: "); fLogger.Print(x)
	#else
		#define LOG(x) std::cout << MEM_WHITE; mem::print(x)
		#define INFO(x) std::cout << MEM_GREEN; mem::printCurrentTime(); mem::printnr(" INFO: "); mem::print(x)
		#define WARNING(x) std::cout << MEM_YELLOW; mem::printCurrentTime(); mem::printnr(" WARNING: "); mem::print(x)
		#define ERROR(x) std::cout << MEM_RED; mem::printCurrentTime(); mem::printnr(" ERROR: "); mem::print(x)
		#define FATAL(x) std::cout << MEM_BOLDRED; mem::printCurrentTime(); mem::printnr(" FATAL ERROR: "); mem::print(x)
	#endif // MEM_LOG_TO_FILE
#else
	#define LOG(x)
	#define INFO(x)
	#define WARNING(x)
	#define ERROR(x)
	#define FATAL(x)
#endif // MEM_LOGGING_ACTIVE

namespace mem
{
	// only logging stuff 

	inline void print()
	{
		std::cout << "\n";
	}

	// no line return
	template <typename T>
	inline void printnr(const T& x)
	{
		std::cout << x;
	}

	template <typename T>
	inline void print(const T& x)
	{
		std::cout << x << "\n";
	}

	inline void print(const glm::vec2& v)
	{
		std::cout << "X: " << v.x << ", " << "Y: " << v.y << "\n";
	}

	inline void print(const glm::vec3& v)
	{
		std::cout << "X: " << v.x << ", " << "Y: " << v.y << ", " << "Z: " << v.z << "\n";
	}

	inline void print(const glm::vec4& v)
	{
		std::cout << "R: " << v.r << ", " << "G: " << v.g << ", " << "B: " << v.b << ", " << "A: " << v.a << "\n";
	}

	template <typename T>
	inline void print(const std::vector<T>& v)
	{
		printnr("{ ");
		for (T obj : v)
		{
			printnr(obj);
			printnr(", ");
		}
		printnr(" }");
	}

	inline void printCurrentTime()
	{
		struct tm buf;
		time_t now = time(0);
		localtime_s(&buf, &now);
		printnr(std::put_time(&buf, "(%Y-%m-%d %X)"));
	}
}

namespace mem
{
	// for easier typing
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T>
	using Ref = std::shared_ptr<T>;

	// utility functions

	inline glm::vec3 colorToNormal(const glm::vec3& color)
	{
		return glm::vec3(color.r / 255, color.g / 255, color.b / 255);
	}

	inline glm::vec4 colorToNormal(const glm::vec4& color)
	{
		return glm::vec4(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
	}

	inline float map(float value, float in_min, float in_max, float out_min, float out_max)
	{
		return (value - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
	}

	// linear interpolation
	inline float lerp(float v0, float v1, float t) 
	{
		return (1 - t) * v0 + t * v1;
	}
	// linear interpolation for vec2
	inline glm::vec2 lerp(const glm::vec2& v0, const glm::vec2& v1, float t)
	{
		return glm::vec2(lerp(v0.x, v1.x, t), lerp(v0.y, v1.y, t));
	}
	// linear interpolation for vec3
	inline glm::vec3 lerp(const glm::vec3& v0, const glm::vec3& v1, float t)
	{
		return glm::vec3(lerp(v0.x, v1.x, t), lerp(v0.y, v1.y, t), lerp(v0.z, v1.z, t));
	}

	// cosine interpolation
	inline float coserp(float v0, float v1, float t)
	{
		float t2 = (1 - cos(t * PI)) / 2;
		return(v0 * (1 - t2) + v1 * t2);
	}
	// cosine interpolation for vec2
	inline glm::vec2 coserp(const glm::vec2& v0, const glm::vec2& v1, float t)
	{
		return glm::vec2(coserp(v0.x, v1.x, t), coserp(v0.y, v1.y, t));
	}
	// cosine interpolation for vec3
	inline glm::vec3 coserp(const glm::vec3& v0, const glm::vec3& v1, float t)
	{
		return glm::vec3(coserp(v0.x, v1.x, t), coserp(v0.y, v1.y, t), coserp(v0.z, v1.z, t));
	}

	inline float sgn(float n)
	{
		return map(signbit(n), 0.f, 1.f, -1.f, 1.f);
	}

	namespace Random
	{
		inline void init() { srand(time(0)); }

		inline int32_t Int(int32_t range) { return (int32_t)(((float)rand() / (float)RAND_MAX) * range); }
		inline float Float(float range) { return ((float)rand() / (float)RAND_MAX) * range; }

		inline glm::ivec2 IVec2(int32_t range) { return glm::ivec2(Int(range), Int(range)); }
		inline glm::vec2 Vec2(float range) { return glm::vec2(Float(range), Float(range)); }

		inline glm::ivec3 IVec3(int32_t range) { return glm::ivec3(Int(range), Int(range), Int(range)); }
		inline glm::vec3 Vec3(float range) { return glm::vec3(Float(range), Float(range), Float(range)); }

		inline glm::ivec4 IVec4(int32_t range) { return glm::ivec4(Int(range), Int(range), Int(range), Int(range)); }
		inline glm::vec4 Vec4(float range) { return glm::vec4(Float(range), Float(range), Float(range), Float(range)); }
	}

	// utility classes

	struct Rect
	{
		int32_t x, y, w, h;

		Rect(int32_t X, int32_t Y, int32_t W, int32_t H)
			: x(X), y(Y), w(W), h(H)
		{}
	};

	struct PolyRect
	{
		glm::vec2 p1, p2, p3, p4;

		PolyRect()
			: p1({ 0, 0 }), p2({ 0, 0 }), p3({ 0, 0 }), p4({ 0, 0 })
		{}

		PolyRect(glm::vec2 P1, glm::vec2 P2, glm::vec2 P3, glm::vec2 P4)
			: p1(P1), p2(P2), p3(P3), p4(P4)
		{}
	};


	inline Rect fromCenter(int32_t centerX, int32_t centerY, int32_t w, int32_t h)
	{
		return Rect(centerX - w/2, centerY - w/2, w, h);
	}

	enum class RectPoints
	{
		CENTER = -1, P1, P2, P3, P4
	};
	
	// angle in radians
	inline PolyRect rotate(const Rect& rect, RectPoints center, float angle)
	{
		switch (center)
		{
		case mem::RectPoints::CENTER:
		{
			glm::vec2 rectCenter = { rect.x + rect.w * 0.5f, rect.y + rect.h * 0.5f };
			float dist1 = glm::distance({ rect.x, rect.y }, rectCenter);
			float dist2 = glm::distance({ rect.x + rect.w, rect.y }, rectCenter);
			float dist3 = glm::distance({ rect.x, rect.y + rect.h }, rectCenter);
			float dist4 = glm::distance({ rect.x + rect.w, rect.y + rect.h }, rectCenter);

			return PolyRect
			(
				{ rectCenter.x + cos(angle + PI * 0.75f) * dist2, rectCenter.y + sin(angle + PI * 0.75f) * dist2 },
				{ rectCenter.x + cos(angle + PI * 0.25f) * dist1, rectCenter.y + sin(angle + PI * 0.25f) * dist1 },
				{ rectCenter.x + cos(angle + PI * 1.25f) * dist3, rectCenter.y + sin(angle + PI * 1.25f) * dist3 },
				{ rectCenter.x + cos(angle + PI * 1.75f) * dist4, rectCenter.y + sin(angle + PI * 1.75f) * dist4 }
			);
		}
		case mem::RectPoints::P1:
		{
			glm::vec2 rectCenter = { rect.x, rect.y };
			float dist2 = glm::distance({ rect.x + rect.w, rect.y }, rectCenter);
			float dist3 = glm::distance({ rect.x, rect.y + rect.h }, rectCenter);
			float dist4 = glm::distance({ rect.x + rect.w, rect.y + rect.h }, rectCenter);

			return PolyRect
			(
				rectCenter,
				{ rectCenter.x + cos(angle) * dist2, rectCenter.y + sin(angle) * dist2 },
				{ rectCenter.x + cos(angle + PI * 0.5f) * dist3, rectCenter.y + sin(angle + PI * 0.5f) * dist3 },
				{ rectCenter.x + cos(angle + PI * 0.25f) * dist4, rectCenter.y + sin(angle + PI * 0.25f) * dist4 }
			);
		}
		case mem::RectPoints::P2:
		{
			glm::vec2 rectCenter = { rect.x + rect.w, rect.y };
			float dist1 = glm::distance({ rect.x, rect.y }, rectCenter);
			float dist3 = glm::distance({ rect.x, rect.y + rect.h }, rectCenter);
			float dist4 = glm::distance({ rect.x + rect.w, rect.y + rect.h }, rectCenter);

			return PolyRect
			(
				rectCenter,
				{ rectCenter.x + cos(angle + PI * 0.5f) * dist1, rectCenter.y + sin(angle + PI * 0.5f) * dist1 },
				{ rectCenter.x + cos(angle + PI) * dist4, rectCenter.y + sin(angle + PI) * dist4 },
				{ rectCenter.x + cos(angle + PI * 0.75f) * dist3, rectCenter.y + sin(angle + PI * 0.75f) * dist3 }
			);
		}
		case mem::RectPoints::P3:
		{
			glm::vec2 rectCenter = { rect.x, rect.y + rect.h };
			float dist1 = glm::distance({ rect.x, rect.y }, rectCenter);
			float dist2 = glm::distance({ rect.x + rect.w, rect.y }, rectCenter);
			float dist4 = glm::distance({ rect.x + rect.w, rect.y + rect.h }, rectCenter);

			return PolyRect
			(
				rectCenter,
				{ rectCenter.x + cos(angle) * dist1, rectCenter.y + sin(angle) * dist1 },
				{ rectCenter.x + cos(angle - PI * 0.5f) * dist4, rectCenter.y + sin(angle - PI * 0.5f) * dist4 },
				{ rectCenter.x + cos(angle - PI * 0.25f) * dist2, rectCenter.y + sin(angle - PI * 0.25f) * dist2 }
			);
		}
		case mem::RectPoints::P4:
		{
			glm::vec2 rectCenter = { rect.x + rect.w, rect.y + rect.h };
			float dist1 = glm::distance({ rect.x, rect.y }, rectCenter);
			float dist2 = glm::distance({ rect.x + rect.w, rect.y }, rectCenter);
			float dist3 = glm::distance({ rect.x, rect.y + rect.h }, rectCenter);

			return PolyRect
			(
				rectCenter,
				{ rectCenter.x + cos(angle + PI * 1.5f) * dist2, rectCenter.y + sin(angle + PI * 1.5f) * dist2 },
				{ rectCenter.x + cos(angle + PI) * dist3, rectCenter.y + sin(angle + PI) * dist3 },
				{ rectCenter.x + cos(angle + PI * 1.25f) * dist1, rectCenter.y + sin(angle + PI * 1.25f) * dist1 }
			);
		}
		default:
		{
			ERROR("Center must be specified");
			return PolyRect();
		}
		}
	}
}