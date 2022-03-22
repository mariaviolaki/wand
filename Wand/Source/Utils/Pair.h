#pragma once

namespace wand
{
	enum class DataType { DT_INT, DT_DOUBLE, DT_BOOL, DT_STRING };

	class Pair
	{
	public:
		Pair(const std::string& name, int value);
		Pair(const std::string& name, double value);
		Pair(const std::string& name, bool value);
		Pair(const std::string& name, const std::string& value);

		std::string GetName() const;
		DataType GetValueType() const;
		int GetIntValue() const;
		double GetDoubleValue() const;
		bool GetBoolValue() const;
		std::string GetStringValue() const;

	private:
		DataType mDataType;
		std::string mName;
		int mIntValue;
		double mDoubleValue;
		bool mBoolValue;
		std::string mStringValue;
	};
}
