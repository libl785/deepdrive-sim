
#include "deepdrive_simulation/DeepDriveSimulation.hpp"
#include "deepdrive_simulation/PySimulationGraphicsSettingsObject.h"
#include "deepdrive_client/DeepDriveClient.hpp"
#include "Public/Server/Messages/DeepDriveServerConfigurationMessages.h"
#include "Public/Server/Messages/DeepDriveServerControlMessages.h"

#include "socket/IP4ClientSocket.hpp"

#include <iostream>

DeepDriveSimulation::DeepDriveSimulation()
{
}

DeepDriveSimulation::~DeepDriveSimulation()
{
}

int32 DeepDriveSimulation::resetSimulation(DeepDriveClient &client, float timeDilation, float startLocation, PySimulationGraphicsSettingsObject *graphicsSettings)
{
	deepdrive::server::ResetSimulationRequest req(client.getClientId());

	deepdrive::server::SimulationConfiguration &cfg = req.configuration;
	cfg.seed = 0;
	cfg.time_dilation = timeDilation;
	cfg.agent_start_location = startLocation;

	if(graphicsSettings)
	{
		deepdrive::server::SimulationGraphicsSettings &gfxSettings = req.graphics_settings;

		gfxSettings.is_fullscreen = graphicsSettings->is_fullscreen;
		gfxSettings.vsync_enabled = graphicsSettings->vsync_enabled;
		gfxSettings.resolution_width = graphicsSettings->resolution_width;
		gfxSettings.resolution_height = graphicsSettings->resolution_height;
		gfxSettings.resolution_scale = graphicsSettings->resolution_scale;
		gfxSettings.texture_quality = static_cast<uint8> (graphicsSettings->texture_quality);
		gfxSettings.shadow_quality = static_cast<uint8> (graphicsSettings->shadow_quality);
		gfxSettings.effect_quality = static_cast<uint8> (graphicsSettings->effect_quality);
		gfxSettings.post_process_level = static_cast<uint8> (graphicsSettings->post_process_level);
		gfxSettings.motion_blur_quality = static_cast<uint8> (graphicsSettings->motion_blur_quality);
		gfxSettings.view_distance = static_cast<uint8> (graphicsSettings->view_distance);
		gfxSettings.ambient_occlusion = static_cast<uint8> (graphicsSettings->ambient_occlusion);
	}


	IP4ClientSocket &socket = client.getSocket();

	int32 res = socket.send(&req, sizeof(req));
	if(res >= 0)
	{
		std::cout << "ResetSimulationRequest sent\n";

		deepdrive::server::ResetSimulationResponse response;
		if(socket.receive(&response, sizeof(response), 1000))
		{
			res = static_cast<int32> (response.reset);
			std::cout << "ResetSimulationResponse received " << client.getClientId() << " " << res << "\n";
		}
		else
			std::cout << "Waiting for ResetSimulationResponse, time out\n";
	}

	return res;
}

int32 DeepDriveSimulation::setSunSimulation(DeepDriveClient &client, uint32 month, uint32 day, uint32 minute, uint32 hour, uint32 speed)
{
	deepdrive::server::SetSunSimulationRequest	req(client.getClientId(), month, day, hour, minute, speed);
	IP4ClientSocket &socket = client.getSocket();

	int32 res = socket.send(&req, sizeof(req));
	if(res >= 0)
	{
		std::cout << "SetSunSimulationRequest sent\n";

		deepdrive::server::SetSunSimulationResponse response;
		if(socket.receive(&response, sizeof(response), 1000))
		{
			res = static_cast<int32> (response.result);
			std::cout << "SetSunSimulationResponse received " << client.getClientId() << " " << res << "\n";
		}
		else
			std::cout << "Waiting for SetSunSimulationRequest, time out\n";
	}

	return res;
}
