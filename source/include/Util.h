// Util.h
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#pragma once
#include <random>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>

namespace SDL
{
	struct Font;
}

namespace Util
{
	namespace Random
	{
		double get(double scale = 1);
		double get(double lower, double upper);
		void cycle();
	};

	struct Colour
	{
		Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) { }
		Colour(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue), a(0xFF) { }
		Colour() : r(0), g(0), b(0), a(0) { }

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Colour operator+(Colour other)
		{
			// stop overflow to zero
			return Colour(std::max(this->r + other.r, 0xFF), std::max(this->g + other.g, 0xFF),
				std::max(this->b + other.b, 0xFF), std::max(this->a + other.a, 0xFF));
		}

		void* toSDL()
		{
			return (void*) this;
		}

		static Colour black() { return Colour(0, 0, 0); }
		static Colour white() { return Colour(0xFF, 0xFF, 0xFF); }

		static Colour red() { return Colour(0xFF, 0, 0); }
		static Colour blue() { return Colour(0, 0, 0xFF); }
		static Colour green() { return Colour(0, 0xFF, 0); }
		static Colour cyan() { return Colour::green() + Colour::blue(); }
		static Colour yellow() { return Colour::red() + Colour::green(); }
		static Colour magenta() { return Colour::blue() + Colour::red(); }
		static Colour random() { return Colour((uint8_t) Util::Random::get(0, 255), (uint8_t) Util::Random::get(0, 255), (uint8_t) Util::Random::get(0, 255)); }
	};



	namespace Font
	{
		SDL::Font* get(std::string name, int size, bool hinting = true);
		void closeAll();
	}
}

template<class T>
using Rc = std::shared_ptr<T>;

namespace Logging
{
	struct Logger
	{
		void Error(const char* fmt, ...);
		void Info(const char* fmt, ...);
		void Warn(const char* fmt, ...);
	};

	std::shared_ptr<Logger> GetGlobalLoggerInstance();
}

#define LOG(fmt, ...)			Logging::GetGlobalLoggerInstance()->Info(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)			Logging::GetGlobalLoggerInstance()->Warn(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...)			Logging::GetGlobalLoggerInstance()->Error(fmt, ##__VA_ARGS__)







#define NS_TO_US(x)				((x) / 1000)
#define NS_TO_MS(x)				(NS_TO_US(x) / 1000)
#define NS_TO_S(x)				(NS_TO_MS(x) / 1000)

#define S_TO_MS(x)				((x) * 1000)
#define S_TO_US(x)				(S_TO_MS(x) * 1000)
#define S_TO_NS(x)				(S_TO_US(x) * 1000)


















