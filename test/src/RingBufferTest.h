#pragma once

#include <gtest/gtest.h>

#include "HyperionUtils/RingBuffer.h"

namespace hyperion::utils::test {

	TEST(RingBufferTest, defaults) {
		auto buffer = RingBuffer<bool, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto& elem : buffer) {
			ASSERT_FALSE(elem);
		}
	}

	TEST(RingBufferTest, initialCapacity) {
		auto buffer = RingBuffer<bool, RingBufferType::NotThreadSafe>(32U);
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), 32ULL);
		ASSERT_TRUE(buffer.empty());

		for(auto& elem : buffer) {
			ASSERT_FALSE(elem);
		}
	}

	TEST(RingBufferTest, initialCapacityAndValue) {
		auto buffer = RingBuffer<bool, RingBufferType::NotThreadSafe>(32U, true);
		ASSERT_EQ(buffer.size(), 32ULL);
		ASSERT_EQ(buffer.capacity(), 32ULL);

		for(auto& elem : buffer) {
			ASSERT_TRUE(elem);
		}
	}

	TEST(RingBufferTest, pushBackAndAt) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.push_back(i);
		}

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			ASSERT_EQ(buffer.at(i), i);
		}
	}

	TEST(RingBufferTest, pushBackAndAtLooping) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.push_back(i);
		}
		for(auto i = static_cast<int>(capacity - 1); i >= 0; --i) {
			buffer.push_back(i);
		}

		for(auto i = 0, j = static_cast<int>(capacity - 1); i < static_cast<int>(capacity);
			++i, --j) {
			ASSERT_EQ(buffer.at(i), j);
		}
	}

	TEST(RingBufferTest, emplaceBackAndAt) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.emplace_back(i);
		}

		for(auto i = 0ULL; i < static_cast<int>(capacity); ++i) {
			ASSERT_EQ(buffer.at(i), i);
		}
	}

	TEST(RingBufferTest, emplaceBackAndAtLooping) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.emplace_back(i);
		}
		for(auto i = static_cast<int>(capacity - 1); i >= 0; --i) {
			buffer.emplace_back(i);
		}

		for(auto i = 0, j = static_cast<int>(capacity - 1); i < static_cast<int>(capacity);
			++i, --j) {
			ASSERT_EQ(buffer.at(i), j);
		}
	}

	TEST(RingBufferTest, reserveAndLooping) {
		uint32_t initialCapacity = 8U;
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>(initialCapacity);
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_TRUE(buffer.empty());
		ASSERT_EQ(buffer.capacity(), initialCapacity);

		for(auto i = 0ULL; i < initialCapacity; ++i) {
			buffer.push_back(static_cast<int>(i));
		}
		for(auto i = 0ULL; i < initialCapacity; ++i) {
			ASSERT_EQ(buffer.at(i), i);
		}
		auto newCapacity = 16U;
		buffer.reserve(newCapacity);
		for(auto i = 0ULL; i < initialCapacity; ++i) {
			ASSERT_EQ(buffer.at(i), i);
		}
		for(auto i = initialCapacity; i < newCapacity + initialCapacity; ++i) {
			buffer.push_back(static_cast<int>(i));
		}
		for(auto i = 0ULL; i < newCapacity; ++i) {
			ASSERT_EQ(buffer.at(i), i + initialCapacity);
		}
		for(auto i = 0ULL; i < newCapacity; ++i) {
			buffer.push_back(static_cast<int>(i));
		}
		for(auto i = 0ULL; i < newCapacity; ++i) {
			ASSERT_EQ(buffer.at(i), i);
		}
	}

	TEST(RingBufferTest, front) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(2);
		ASSERT_EQ(buffer.front(), 2);
	}

	TEST(RingBufferTest, back) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(2);
		buffer.push_back(1);
		ASSERT_EQ(buffer.back(), 1);
	}

	TEST(RingBufferTest, insert) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(2);
		buffer.insert(buffer.begin(), 1);
		ASSERT_EQ(buffer.front(), 1);
		ASSERT_EQ(buffer.back(), 2);
	}

	TEST(RingBufferTest, insertLooped) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0ULL; i < capacity; ++i) {
			buffer.push_back(static_cast<int>(i));
		}

		buffer.insert(buffer.begin(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.front(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.at(1), 0);
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity - 2));
	}

	TEST(RingBufferTest, insertLoopedAndAHalf) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		auto numWrites = static_cast<int>(capacity * 1.5);
		for(auto i = 0; i < numWrites; ++i) {
			buffer.push_back(i);
		}

		buffer.insert(buffer.begin(), numWrites);
		ASSERT_EQ(buffer.front(), numWrites);
		ASSERT_EQ(buffer.at(1), numWrites - static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), numWrites - 2);
	}

	TEST(RingBufferTest, insertEmplace) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(2);
		buffer.insert_emplace(buffer.begin(), 1);
		ASSERT_EQ(buffer.front(), 1);
		ASSERT_EQ(buffer.back(), 2);
	}

	TEST(RingBufferTest, insertEmplaceLooped) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0ULL; i < capacity; ++i) {
			buffer.push_back(static_cast<int>(i));
		}

		buffer.insert_emplace(buffer.begin(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.front(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.at(1), 0);
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity - 2));
	}

	TEST(RingBufferTest, insertEmplaceLoopedAndAHalf) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		auto numWrites = static_cast<int>(capacity * 1.5);
		for(auto i = 0; i < numWrites; ++i) {
			buffer.push_back(i);
		}

		buffer.insert_emplace(buffer.begin(), numWrites);
		ASSERT_EQ(buffer.front(), numWrites);
		ASSERT_EQ(buffer.at(1), numWrites - static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), numWrites - 2);
	}

	TEST(RingBufferTest, erase) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(3);
		buffer.push_back(5);

		ASSERT_EQ(buffer.size(), 2);
		ASSERT_EQ(buffer.back(), 5);
		auto iter = buffer.erase(buffer.end() - 1);
		ASSERT_EQ(buffer.size(), 1);
		ASSERT_EQ(buffer.back(), 3);
		ASSERT_EQ(iter, buffer.end());
	}

	TEST(RingBufferTest, eraseFullFromEnd) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 1);
		const auto size = buffer.size();
		auto iter = buffer.erase(buffer.end() - 1);
		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - 1);
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 2);
		ASSERT_EQ(iter, buffer.begin() + (size - 1));
	}

	TEST(RingBufferTest, eraseFullFromMiddle) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 1);
		const auto size = buffer.size();
		auto iter = buffer.erase(buffer.end() - 4);
		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - 1);
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 1);
		ASSERT_EQ(iter, buffer.begin() + (size - 4));
	}

	TEST(RingBufferTest, eraseFullAndAHalfFromEnd) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		auto numWrites = static_cast<int>(capacity * 1.5);
		for(auto i = 0; i < numWrites; ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), numWrites - 1);
		const auto size = buffer.size();
		auto iter = buffer.erase(buffer.end() - 1);
		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - 1);
		ASSERT_EQ(buffer.back(), numWrites - 2);
		ASSERT_EQ(iter, buffer.begin() + (size - 1));
	}

	TEST(RingBufferTest, eraseFullAndAHalfFromMiddle) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		auto numWrites = static_cast<int>(capacity * 1.5);
		for(auto i = 0; i < numWrites; ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), numWrites - 1);
		const auto size = buffer.size();
		auto iter = buffer.erase(buffer.end() - 4);
		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - 1);
		ASSERT_EQ(buffer.back(), numWrites - 1);
		ASSERT_EQ(iter, buffer.begin() + (size - 4));
	}

	TEST(RingBufferTest, eraseRange) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		buffer.push_back(3);
		buffer.push_back(5);
		buffer.push_back(6);

		ASSERT_EQ(buffer.size(), 3);
		ASSERT_EQ(buffer.back(), 6);
		auto iter = buffer.erase(buffer.begin() + 1, buffer.end());
		ASSERT_EQ(buffer.size(), 1);
		ASSERT_EQ(buffer.back(), 3);
		ASSERT_EQ(iter, buffer.end());
	}

	TEST(RingBufferTest, eraseRangeFull) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		for(auto i = 0; i < static_cast<int>(capacity); ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 1);
		auto iter = buffer.erase(buffer.end() - 2, buffer.end());
		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - 2);
		ASSERT_EQ(buffer.back(), static_cast<int>(capacity) - 3);
		ASSERT_EQ(iter, buffer.end());
	}

	TEST(RingBufferTest, eraseRangeFullAndAHalf) {
		auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
		constexpr auto capacity = RingBuffer<int, RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY;
		ASSERT_EQ(buffer.size(), 0ULL);
		ASSERT_EQ(buffer.capacity(), capacity);
		ASSERT_TRUE(buffer.empty());

		auto numWrites = static_cast<int>(capacity * 1.5);
		for(auto i = 0; i < numWrites; ++i) {
			buffer.push_back(i);
		}

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity));
		ASSERT_EQ(buffer.back(), numWrites - 1);
		const auto startEraseIndex = 5;
		const auto numToErase = 5;
		const auto startIter = buffer.begin() + startEraseIndex;
		const auto endIter = startIter + numToErase;
		const auto valToCompare = buffer.at(startEraseIndex + numToErase);
		const auto backVal = buffer.back();
		const auto frontVal = buffer.front();

		const auto iter = buffer.erase(startIter, endIter);

		ASSERT_EQ(buffer.size(), static_cast<int>(capacity) - numToErase);
		ASSERT_EQ(buffer.back(), backVal);
		ASSERT_EQ(buffer.front(), frontVal);
		ASSERT_EQ(buffer.at(startEraseIndex), valToCompare);
		ASSERT_EQ(iter, buffer.begin() + startEraseIndex);
	}
	//
	// TEST(RingBufferTest, popBack) {
	//	auto buffer = RingBuffer<int, RingBufferType::NotThreadSafe>();
	//	ASSERT_EQ(buffer.size(), 0ULL);
	//	ASSERT_EQ(buffer.capacity(), RingBuffer<int,
	// RingBufferType::NotThreadSafe>::DEFAULT_CAPACITY); 	ASSERT_TRUE(buffer.empty());
	//
	//	buffer.push_back(1);
	//	buffer.push_back(2);
	//	ASSERT_EQ(buffer.size(), 2);
	//	ASSERT_EQ(buffer.back(), 2);
	//	ASSERT_EQ(buffer.pop_back(), 2);
	//	ASSERT_EQ(buffer.size(), 1);
	//	ASSERT_EQ(buffer.back(), 1);
	// }
} // namespace hyperion::utils::test
