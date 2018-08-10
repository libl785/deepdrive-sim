// Fill out your copyright notice in the Description page of Project Settings.

#include "DeepDrivePluginPrivatePCH.h"
#include "DeepDrivePlugin.h"
#include "Public/CaptureSink/CaptureSinkComponentBase.h"


UCaptureSinkComponentBase::UCaptureSinkComponentBase()
{
}



void UCaptureSinkComponentBase::begin(double timestamp, uint32 sequenceNumber, const FDeepDriveDataOut &deepDriveData)
{

}

bool UCaptureSinkComponentBase::setCaptureBuffer(int32 cameraId, EDeepDriveCameraType cameraType, CaptureBuffer &sceneCaptureBuffer, CaptureBuffer *depthCaptureBuffer)
{
	return false;
}

void UCaptureSinkComponentBase::flush()
{

}
