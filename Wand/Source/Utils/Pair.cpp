#include "WandPCH.h"
#include "Pair.h"

namespace wand
{
	Pair::Pair(const std::string& name, int value)
		: mDataType(DataType::DT_INT), mName(name),
		mIntValue(value), mDoubleValue(0.0), mBoolValue(false), mStringValue("")
	{}

	Pair::Pair(const std::string& name, double value)
		: mDataType(DataType::DT_DOUBLE), mName(name),
		mIntValue(0), mDoubleValue(value), mBoolValue(false), mStringValue("")
	{}

	Pair::Pair(const std::string& name, bool value)
		: mDataType(DataType::DT_BOOL), mName(name),
		mIntValue(0), mDoubleValue(0.0), mBoolValue(value), mStringValue("")
	{}

	Pair::Pair(const std::string& name, const std::string& value)
		: mDataType(DataType::DT_STRING), mName(name),
		mIntValue(0), mDoubleValue(0.0), mBoolValue(false), mStringValue(value)
	{}

	std::string Pair::GetName() const { return mName; }

	DataType Pair::GetValueType() const { return mDataType; }

	int Pair::GetIntValue() const { return mIntValue; }

	double Pair::GetDoubleValue() const { return mDoubleValue; }

	bool Pair::GetBoolValue() const { return mBoolValue; }

	std::string Pair::GetStringValue() const { return mStringValue; }
}