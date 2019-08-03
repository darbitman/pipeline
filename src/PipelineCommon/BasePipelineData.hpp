#ifndef BASEPIPELINEDATA_HPP
#define BASEPIPELINEDATA_HPP

namespace sc
{
class BasePipelineData
{
public:
    explicit BasePipelineData(bool bFlagToShutdown = false);

    virtual ~BasePipelineData();

    virtual void SetShutdownFlag();

    virtual void ResetShutdownFlag();

    virtual bool GetShutdownFlag() const;

    // deleted to prevent misuse
    BasePipelineData(const BasePipelineData&) = delete;
    BasePipelineData(const BasePipelineData&&) = delete;
    BasePipelineData& operator=(const BasePipelineData&) = delete;
    BasePipelineData& operator=(const BasePipelineData&&) = delete;

private:
    bool bFlagToShutdown_;
};
}  // namespace sc

#endif
