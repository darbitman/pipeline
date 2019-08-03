#include "BasePipelineData.hpp"

namespace sc
{
BasePipelineData::BasePipelineData(bool bFlagToShutdown) : bFlagToShutdown_(bFlagToShutdown) {}

BasePipelineData::~BasePipelineData() {}

void BasePipelineData::SetShutdownFlag() { bFlagToShutdown_ = true; }

void BasePipelineData::ResetShutdownFlag() { bFlagToShutdown_ = false; }

bool BasePipelineData::GetShutdownFlag() const { return bFlagToShutdown_; }

}  // namespace sc
