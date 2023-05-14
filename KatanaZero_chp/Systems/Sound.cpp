#include "stdafx.h"
#include "Sound.h"

Sound::Sound()
{
	System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, nullptr);
}

Sound::~Sound()
{
	for (auto& node : soundList)
	{
		node.second->channel->stop();
		node.second->sound->release();
		node.second.reset();
	}
	system->release();
	system->close();
	soundList.clear();
}

void Sound::Update()
{
	system->update();
}

bool Sound::AddSound(const string& key, const wstring& path, bool bLoop, bool canMultiPlay)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
		return false;

	auto temp = make_shared<SoundNode>();
	if (system->createSound(String::ToString(path).c_str(), FMOD_DEFAULT, nullptr, &temp->sound))
		return false;

	if (bLoop)
	{
		temp->bLoop = true;
		temp->sound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		temp->bLoop = false;
		temp->sound->setMode(FMOD_LOOP_OFF);
	}

	temp->path = path;
	temp->canMulti = canMultiPlay;

	return false;
}

bool Sound::DeleteSoun(const string& key)
{
	auto iter = soundList.find(key);

	if (iter == soundList.end())
		return false;

	iter->second->channel->stop();
	iter->second->sound->release();
	iter->second.reset();

	soundList.erase(iter);

	return false;
}

void Sound::Play(const string& key)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
	{
		if (iter->second->canMulti)
			system->playSound(iter->second->sound, nullptr, false, &iter->second->channel);
		else
		{
			bool isPlaying;
			iter->second->channel->isPlaying(&isPlaying);
			if (!isPlaying)
				system->playSound(iter->second->sound, nullptr, false, &iter->second->channel);
		}
	}
}

void Sound::Stop(const string& key)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
		iter->second->channel->stop();
}

void Sound::Pause(const string& key)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
		iter->second->channel->setPaused(true);
}

void Sound::Resume(const string& key)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
		iter->second->channel->setPaused(false);
}

void Sound::SetVolume(const string& key, float channelVolume)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
	{
		iter->second->channelVolume = channelVolume;
		iter->second->channel->setVolume(volume * channelVolume);
	}
}

void Sound::SetMasterVolume(float volume)
{
	this->volume = volume;
}

void Sound::GUI(const string& key)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
	{
		string objName = "Sound" + key;
		string fileName = Path::GetFileName(String::ToString(iter->second->path));
		string GUIFileName = "File Name : " + fileName;

		if (ImGui::BeginMenu(objName.c_str()))
		{
			ImGui::Text(objName.c_str());
			ImGui::Text(GUIFileName.c_str());

			//Button
			if (ImGui::Button("Play", ImVec2(50, 30)))
				Play(key);
			ImGui::SameLine();
			if (ImGui::Button("Stop", ImVec2(50, 30)))
				Stop(key);
			ImGui::SameLine();
			if (ImGui::Button("Pause", ImVec2(50, 30)))
				Pause(key);
			ImGui::SameLine();
			if (ImGui::Button("Resume", ImVec2(50, 30)))
				Resume(key);

			if (ImGui::Button("ChangeSound", ImVec2(218, 30)))
				ChangeSoundFunc(key);

			if (ImGui::SliderFloat("Volume", &iter->second->channelVolume, 0.0f, 1.0f))
				SetVolume(key, iter->second->channelVolume);

			if (ImGui::Checkbox("Mute", &iter->second->bMute))
				iter->second->channel->setMute(iter->second->bMute);

			if (ImGui::Checkbox("Loop", &iter->second->bLoop))
			{
				if (iter->second->bLoop)
					iter->second->channel->setMode(FMOD_LOOP_NORMAL);
				else
					iter->second->channel->setMode(FMOD_LOOP_OFF);
			}

			ImGui::Checkbox("MultiPlay", &iter->second->canMulti);

			ImGui::EndMenu();
		}
	}
}

void Sound::ChangeSoundFunc(const string& key, const wstring& path)
{
	auto iter = soundList.find(key);

	if (iter != soundList.end())
	{
		if (path.empty())
		{
			function<void(wstring)> func = bind(&Sound::ChangeSoundFunc, this, key, placeholders::_1);
			Path::OpenFileDialog(L"", Path::SoundFilter, L"_Sounds/", func, gHandle);
		}
		else
		{
			iter->second->channel->stop();
			iter->second->path = path;
			system->createSound(String::ToString(path).c_str(), FMOD_DEFAULT, nullptr, &iter->second->sound);
		}
	}
}
