#pragma once

#include "IntVector4.h"

namespace Monad
{
	enum class Register : unsigned int
	{
		X,
		Y,
		Z,
		W
	};

	class Alu
	{
	public:
		const IntVector4& GetRegisters() const { return m_register; }

		void Inp(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] = value;
		}

		void Add(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] += value;
		}

		void Add(Register destination, Register source)
		{
			m_register[static_cast<size_t>(destination)] += m_register[static_cast<size_t>(source)];
		}

		void Mul(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] *= value;
		}

	private:
		IntVector4 m_register{};
	};
}
