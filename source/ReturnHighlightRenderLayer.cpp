#include "BinjaReturnHighlighter/ReturnHighlightRenderLayer.hpp"

#include <algorithm>
#include <vector>

#include <binaryninjaapi.h>
#include <binaryninjacore.h>
#include <highlevelilinstruction.h>
#include <lowlevelilinstruction.h>
#include <mediumlevelilinstruction.h>

using namespace BinaryNinja;

namespace {
	constexpr int AlphaSolid = 255;

	void HighLightReturnLine(DisassemblyTextLine& line)
	{
		line.highlight.style = StandardHighlightColor;
		line.highlight.color = BlueHighlightColor;
		line.highlight.mixColor = NoHighlightColor;
		line.highlight.mix = 0;
		line.highlight.r = 0;
		line.highlight.g = 0;
		line.highlight.b = 0;
		line.highlight.alpha = AlphaSolid;
	}

	bool LineContainsKeywordToken(DisassemblyTextLine& line)
	{
		return std::any_of(line.tokens.begin(), line.tokens.end(), [](const auto& token) {
			return token.type == KeywordToken;
		});
	}
}  // namespace

void ReturnHighlightRenderLayer::ApplyToLowLevelILBlock(
	const Ref<BasicBlock> block, std::vector<DisassemblyTextLine>& lines)
{
	Ref<LowLevelILFunction> const llilFunc = block->GetLowLevelILFunction();
	for (auto& line : lines)
	{
		bool isReturn = false;
		LowLevelILInstruction const instr = llilFunc->GetInstruction(line.instrIndex);
		isReturn = instr.operation == LLIL_RET;

		if (isReturn && LineContainsKeywordToken(line))
		{
			HighLightReturnLine(line);
		}
	}
}

void ReturnHighlightRenderLayer::ApplyToMediumLevelILBlock(
	const Ref<BasicBlock> block, std::vector<DisassemblyTextLine>& lines)
{
	Ref<MediumLevelILFunction> const mlilFunc = block->GetMediumLevelILFunction();
	for (auto& line : lines)
	{
		bool isReturn = false;
		MediumLevelILInstruction const instr = mlilFunc->GetInstruction(line.instrIndex);
		isReturn = instr.operation == MLIL_RET;

		if (isReturn && LineContainsKeywordToken(line))
		{
			HighLightReturnLine(line);
		}
	}
}

void ReturnHighlightRenderLayer::ApplyToHighLevelILBlock(
	Ref<BasicBlock> const block, std::vector<DisassemblyTextLine>& lines)
{
	Ref<HighLevelILFunction> const hlilFunc = block->GetHighLevelILFunction();
	for (auto& line : lines)
	{
		bool isReturn = false;
		HighLevelILInstruction const instr = hlilFunc->GetInstruction(line.instrIndex);
		isReturn = instr.operation == HLIL_RET;

		if (isReturn && LineContainsKeywordToken(line))
		{
			HighLightReturnLine(line);
		}
	}
}

void ReturnHighlightRenderLayer::ApplyToHighLevelILBody(
	const Ref<Function> function, std::vector<LinearDisassemblyLine>& lines)
{
	Ref<HighLevelILFunction> const hlilFunc = function->GetHighLevelIL();
	for (auto& linearLine : lines)
	{
		DisassemblyTextLine& line = linearLine.contents;

		// Need to check for a keyword token. Not sure if there's a more efficient way
		if (HighLevelILInstruction const instr = hlilFunc->GetInstruction(line.instrIndex);
			instr.operation == HLIL_RET && LineContainsKeywordToken(line))
		{
			HighLightReturnLine(line);
		}
	}
}
