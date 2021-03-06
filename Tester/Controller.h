#pragma once
#include <wrl/client.h>
#include "DeviceResources.h"
#include "Stopwatch.h"
#include "Participant.h"
#include "Utils.h"
#include <filesystem>

constexpr auto FAILURE = L"Success3.wav";

namespace Experiment
{
	using Image = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;


	class Controller
	{
	public:
		Controller(Run& run, DX::DeviceResources* deviceResources);

		[[nodiscard]] Utils::Timer<>* GetFlickerTimer() const { return m_flickerTimer.get(); }

		StereoFlickerArtefact<Image> GetCurrentImage()
		{
			return GetFlickerStereoImageFrom(m_run.files[m_currentImageIndex]);
		}

		int numberOfImages() const { return m_run.files.size(); }

		int m_currentImageIndex = 0;

	private:

		[[nodiscard]] Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ToResource(const std::filesystem::path& image) const;

		StereoFlickerArtefact<Image> GetFlickerStereoImageFrom(const StereoFlickerArtefact<std::filesystem::path>& views) const;

		DX::DeviceResources* m_deviceResources;
		Experiment::Run m_run;

		std::unique_ptr<Utils::Timer<>> m_flickerTimer;

	};

}