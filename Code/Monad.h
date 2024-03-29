#pragma once

#include "IntVector4.h"

#include <vector>

namespace Monad
{
	enum Register : int
	{
		X,
		Y,
		Z,
		W
	};

	enum Inst : int
	{
		Inp,
		AddV,
		AddR,
		MulV,
		MulR,
		DivV,
		DivR,
		ModV,
		ModR,
		EqlV,
		EqlR
	};

	class Alu
	{
	public:
		const IntVector4& GetRegisters() const { return m_register; }

		bool IsCrashed() const { return m_isCrashed; }

		void Inp(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] = value;
		}

		void AddV(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] += value;
		}

		void AddR(Register destination, Register source)
		{
			m_register[static_cast<size_t>(destination)] += m_register[static_cast<size_t>(source)];
		}

		void MulV(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] *= value;
		}

		void MulR(Register destination, Register source)
		{
			m_register[static_cast<size_t>(destination)] *= m_register[static_cast<size_t>(source)];
		}

		void DivV(Register destination, int value)
		{
			if (value == 0)
			{
				m_isCrashed = true;
				return;
			}
			m_register[static_cast<size_t>(destination)] /= value;
		}

		void DivR(Register destination, Register source)
		{
			if (m_register[static_cast<size_t>(source)] == 0)
			{
				m_isCrashed = true;
				return;
			}
			m_register[static_cast<size_t>(destination)] /= m_register[static_cast<size_t>(source)];
		}

		void ModV(Register destination, int value)
		{
			if (m_register[static_cast<size_t>(destination)] < 0 ||
				value <= 0)
			{
				m_isCrashed = true;
				return;
			}
			m_register[static_cast<size_t>(destination)] %= value;
		}

		void ModR(Register destination, Register source)
		{
			if (m_register[static_cast<size_t>(destination)] < 0 ||
				m_register[static_cast<size_t>(source)] <= 0)
			{
				m_isCrashed = true;
				return;
			}
			m_register[static_cast<size_t>(destination)] %= m_register[static_cast<size_t>(source)];
		}

		void EqlV(Register destination, int value)
		{
			m_register[static_cast<size_t>(destination)] = m_register[static_cast<size_t>(destination)] == value;
		}

		void EqlR(Register destination, Register source)
		{
			m_register[static_cast<size_t>(destination)] = m_register[static_cast<size_t>(destination)] == m_register[static_cast<size_t>(source)];
		}

	private:
		IntVector4 m_register{};
		bool m_isCrashed = false;
	};

	struct Instruction
	{
		Inst inst{};
		int a{};
		int b{};
	};

	using Program = std::vector<Instruction>;
	struct Memory {};

	class Processor
	{
	public:
		Processor(const Program& program, const Memory& memory) {}

		const Alu& GetAlu() const { return m_alu; }

		void Run() {}

	private:
		Alu m_alu;
	};
}
