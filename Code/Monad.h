#pragma once

#include "IntVector4.h"

namespace Monad
{
	class Alu
	{
	public:
		const IntVector4& GetRegisters() const { return m_register; }

		void Inp(size_t coord, int value)
		{
			m_register[coord] = value;
		}

	private:
		IntVector4 m_register{};
	};
}
