#include "stdafx.h"
/*
 * WengoPhone, a voice over Internet phone
 * Copyright (C) 2004-2007  Wengo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "QtAudioSettings.h"

#include "ui_AudioSettings.h"

#include <model/config/ConfigManager.h>
#include <model/config/Config.h>
#include <model/profile/UserProfile.h>
#include <model/phoneline/IPhoneLine.h>
#include <model/wenbox/EnumWenboxStatus.h>

#include <control/CWengoPhone.h>
#include <control/profile/CUserProfile.h>
#include <control/profile/CUserProfileHandler.h>

#include <presentation/qt/QtWengoPhone.h>

#include <sound/AudioDeviceManager.h>
#include <sound/Sound.h>
#include <sound/VolumeControl.h>
#include <sound/AudioDevice.h>
#include <qtutil/StringListConvert.h>
#include <qtutil/SafeConnect.h>
#include <util/SafeDelete.h>

#include <QtGui/QtGui>

static AudioDevice getAudioDeviceFromComboBox(QComboBox* comboBox, const std::list<AudioDevice> deviceList) {
	std::string concatString = qPrintable( comboBox->itemData(comboBox->currentIndex()).toString());
	for (std::list<AudioDevice>::const_iterator it = deviceList.begin();
		it != deviceList.end();
		++it) {
		if (it->getData().toString() == concatString) {
			return *it;
		}
	}
	return AudioDevice();
}

QtAudioSettings::QtAudioSettings(CWengoPhone & cWengoPhone, QWidget * parent)
	: QWidget(parent),
	_cWengoPhone(cWengoPhone) {

	_ui = new Ui::AudioSettings();
	_ui->setupUi(this);

	//SAFE_CONNECT(_ui->makeTestCallButton, SIGNAL(pressed()), SLOT(makeTestCallClicked()));	zhenHua.sun 2010-08-01
	SAFE_CONNECT(_ui->testOutputDeviceButton, SIGNAL(pressed()), SLOT(testOutputDevice()));
	/* zhenHua.sun 2010-08-01
	SAFE_CONNECT(_ui->testRingingDeviceButton, SIGNAL(pressed()), SLOT(testRingingDevice()));
	SAFE_CONNECT(_ui->AdvButton, SIGNAL(pressed()), SLOT(AdvPressed()));
	SAFE_CONNECT(_ui->UpButton, SIGNAL(pressed()), SLOT(UpPressed()));
	SAFE_CONNECT(_ui->DownButton, SIGNAL(pressed()), SLOT(DownPressed()));
	SAFE_CONNECT(_ui->ResetButton, SIGNAL(pressed()), SLOT(ResetPressed()));
	*/

	SAFE_CONNECT(_ui->saveButton, SIGNAL(clicked()), SLOT(saveButtonClicked()));
	SAFE_CONNECT(_ui->_inputVolumeSlider, SIGNAL(valueChanged(int)),SLOT(setVolume(int)) );
	SAFE_CONNECT(_ui->_outputVolumeSlider, SIGNAL(valueChanged(int)),SLOT(setVolume(int)) );
	SAFE_CONNECT_RECEIVER(_cWengoPhone._qtWengoPhone,SIGNAL(ActionSetVolumeSignal(int,char)),this,SLOT(TeleSetVolumeCommand(int,char)));//Add By LZY 2010-10-05 绑定响应SetVolume动作Signal的函数
	//_ui->AdvGroupBox->setVisible(false);		zhenHua.sun 2010-08-01

	/* zhenHua.sun 2010-08-01
#ifndef CUSTOM_ACCOUNT
	_ui->enableWenboxCheckBox->setVisible(false);
#endif
	*/

	//����û�õĿؼ�

	/* zhenHua.sun 2010-08-01
	_ui->ringingDeviceComboBox->setVisible(false);
	_ui->testRingingDeviceButton->setVisible(false);
	
	_ui->halfDuplexCheckBox->setVisible(false);
	_ui->makeTestCallButton->setVisible(false);
	_ui->AdvButton->setVisible(false);		zhenHua.sun 2010-08-01
	*/

	readConfig();

	//隐藏取消按钮  zhenHua.sun 2010-08-20
	_ui->cancelButton_2->hide();
}

QtAudioSettings::~QtAudioSettings() {
	disconnect(_cWengoPhone._qtWengoPhone,SIGNAL(ActionSetVolumeSignal(int,char)),this,SLOT(TeleSetVolumeCommand(int,char)));//Add By LZY 2010-10-05 解绑响应SetVolume动作Signal的函数
	OWSAFE_DELETE(_ui);
}

QString QtAudioSettings::getName() const {
	return tr("Audio");
}

QString QtAudioSettings::getTitle() const {
	return tr("Audio Settings");
}

QString QtAudioSettings::getIconName() const {
	return "audio";
}

void QtAudioSettings::saveConfig() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	AudioDevice device = getAudioDeviceFromComboBox(_ui->inputDeviceComboBox, AudioDeviceManager::getInstance().getInputDeviceList());
	config.set(Config::AUDIO_INPUT_DEVICEID_KEY, device.getData());

	device = getAudioDeviceFromComboBox(_ui->outputDeviceComboBox, AudioDeviceManager::getInstance().getOutputDeviceList());
	config.set(Config::AUDIO_OUTPUT_DEVICEID_KEY, device.getData());

	//device = getAudioDeviceFromComboBox(_ui->ringingDeviceComboBox, AudioDeviceManager::getInstance().getOutputDeviceList()); zhenHua.sun 2010-08-01
	config.set(Config::AUDIO_RINGER_DEVICEID_KEY, device.getData());

	int audioChannels  = 1;
	int audioSampleRate = 16000;
	int audioBitsPerSample = 16;
	//audio input codec zhenHua.sun 2010-08-01
	config.set( Config::AUDIO_CHANNELS , audioChannels );

	config.set( Config::AUDIO_SAMPLE_RATE , audioSampleRate );

	config.set( Config::AUDIO_BITS_PER_SAMPLE , audioBitsPerSample );

	String codecParam = "SPEEX";			//以'/'为间隔
	codecParam += ( "/" +String::fromNumber( audioSampleRate ));
	codecParam += ("/" + String::fromNumber( audioBitsPerSample ));
	codecParam += ("/" + String::fromNumber( audioChannels ));

	StringList saveCodec;
	saveCodec += codecParam ;
	config.set(Config::AUDIO_CODEC_LIST_KEY, saveCodec);

	//弹出确定按钮   zhenHua.sun 2010-08-20
	QTextCodec::setCodecForTr( QTextCodec::codecForName("utf-8"));
	QMessageBox::information(getWidget(), 
		QObject::tr("确认"),
		QObject::tr("保存成功"), 
		QMessageBox::Ok);

	/*  zhenHua.sun 2010-08-01
	// advanced
	StringList saveCodec;
	int nbCodec = _ui->audioCodecListWidget->count();
	for (int i = 0; i < nbCodec; ++i) {
		std::string audioCodec = _ui->audioCodecListWidget->item(i)->text().toStdString();
		// HACK: PHAPI_SPEEXWB_REPLACES_G726WB_HACK
		if (audioCodec == "SPEEX/16000") {
			audioCodec = "G726-64wb/16000";
		}
		////
		saveCodec += audioCodec;
	}
	config.set(Config::AUDIO_CODEC_LIST_KEY, saveCodec);
	////

	// Wenbox
	if (EnumWenboxStatus::toWenboxStatus(config.getWenboxEnable()) != EnumWenboxStatus::WenboxStatusNotConnected) {
		if (_ui->enableWenboxCheckBox->isChecked()) {
			config.set(Config::WENBOX_ENABLE_KEY, EnumWenboxStatus::toString(EnumWenboxStatus::WenboxStatusEnable));
		} else {
			config.set(Config::WENBOX_ENABLE_KEY, EnumWenboxStatus::toString(EnumWenboxStatus::WenboxStatusDisable));
		}
	}
	
	config.set(Config::AUDIO_HALFDUPLEX_KEY, _ui->halfDuplexCheckBox->isChecked());
	*/
}

void QtAudioSettings::readConfig() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	//inputDeviceList
	_ui->inputDeviceComboBox->clear();

#ifdef OS_LINUX
	bool savedSettingsFound = false;
	AudioDevice tmpDev(config.getAudioInputDeviceId());
#endif

	std::list<AudioDevice> inputDeviceList = AudioDeviceManager::getInstance().getInputDeviceList();
	for (std::list<AudioDevice>::const_iterator it = inputDeviceList.begin();			
		it != inputDeviceList.end();
		++it) {
		if( it==inputDeviceList.begin() )
			continue;				//不要第一个，因为directshow中无法得到 zhenHua.sun 2010-10-27
		_ui->inputDeviceComboBox->addItem(
			QString::fromLocal8Bit((*it).getName().c_str()),
			QString::fromLocal8Bit((*it).getData().toString().c_str())
		);
#ifdef OS_LINUX
		if ((*it).getData() == tmpDev.getData()) {
			savedSettingsFound = true;
		}
#endif
	}

#ifdef OS_LINUX
	if (!savedSettingsFound) {
		_ui->outputDeviceComboBox->addItem(
			QString::fromUtf8(tmpDev.getName().c_str()),
			QString::fromStdString(tmpDev.getData().toString())
		);
	}
#endif
	QString currentInputDeviceId = 
		QString::fromLocal8Bit(config.getAudioInputDeviceId().toString().c_str());
	int index = _ui->inputDeviceComboBox->findData(currentInputDeviceId);
	if( index>0 )
		_ui->inputDeviceComboBox->setCurrentIndex(	index	);
	else
		_ui->inputDeviceComboBox->setCurrentIndex( 0 );
	////

	//outputDeviceList
	_ui->outputDeviceComboBox->clear();

#ifdef OS_LINUX
	savedSettingsFound = false;
	tmpDev = AudioDevice(config.getAudioOutputDeviceId());
#endif
	std::list<AudioDevice> outputDeviceList = AudioDeviceManager::getInstance().getOutputDeviceList();
	for (std::list<AudioDevice>::const_iterator it = outputDeviceList.begin();
		it != outputDeviceList.end();
		++it) {
		if( it==outputDeviceList.begin() )
			continue;				//不要第一个，因为directshow中无法得到 zhenHua.sun 2010-10-27
		_ui->outputDeviceComboBox->addItem(
			QString::fromLocal8Bit((*it).getName().c_str()),
			QString::fromLocal8Bit((*it).getData().toString().c_str())
		);
#ifdef OS_LINUX
		if ((*it).getData() == tmpDev.getData()) {
			savedSettingsFound = true;
		}
#endif
	}

#ifdef OS_LINUX
	if (!savedSettingsFound) {
		_ui->outputDeviceComboBox->addItem(
			QString::fromUtf8(tmpDev.getName().c_str()),
			QString::fromStdString(tmpDev.getData().toString())
		);
	}
#endif
	QString currentOutputDeviceId = 
		QString::fromLocal8Bit(config.getAudioOutputDeviceId().toString().c_str());
	index = _ui->outputDeviceComboBox->findData( currentOutputDeviceId );
	_ui->outputDeviceComboBox->setCurrentIndex(  
		index>0 ? index : 0
	);

	////
	


	/* zhenHua.sun 2010-08-01
	_ui->ringingDeviceComboBox->clear();   
#ifdef OS_LINUX
	savedSettingsFound = false;
	tmpDev = AudioDevice(config.getAudioOutputDeviceId());
#endif
	for (std::list<AudioDevice>::const_iterator it = outputDeviceList.begin();
		it != outputDeviceList.end();
		++it) {
		_ui->ringingDeviceComboBox->addItem(
			QString::fromUtf8((*it).getName().c_str()),
			QString::fromStdString((*it).getData().toString())
		);
#ifdef OS_LINUX
		if ((*it).getData() == tmpDev.getData()) {
			savedSettingsFound = true;
		}
#endif
	}

#ifdef OS_LINUX
	if (!savedSettingsFound) {
		_ui->ringingDeviceComboBox->addItem(
			QString::fromUtf8(tmpDev.getName().c_str()),
			QString::fromStdString(tmpDev.getData().toString())
		);
	}
#endif

	QString currentRingerDeviceId = 
		QString::fromUtf8(config.getAudioRingerDeviceId().toString().c_str());

	_ui->ringingDeviceComboBox->setCurrentIndex(
		_ui->ringingDeviceComboBox->findData(currentRingerDeviceId)
	);
	////
	
	// advanced
	fillAudioCodecList();

	// Wenbox
	EnumWenboxStatus::WenboxStatus wenboxStatus = EnumWenboxStatus::toWenboxStatus(config.getWenboxEnable());
	_ui->enableWenboxCheckBox->setEnabled(wenboxStatus != EnumWenboxStatus::WenboxStatusNotConnected);
	_ui->enableWenboxCheckBox->setChecked(wenboxStatus == EnumWenboxStatus::WenboxStatusEnable);

	_ui->halfDuplexCheckBox->setChecked(config.getAudioHalfDuplex());

	*/
	initVolumeSlider(_ui->_inputVolumeSlider);
	initVolumeSlider(_ui->_outputVolumeSlider);
}

void QtAudioSettings::makeTestCallClicked() {
	CUserProfile * cUserProfile = _cWengoPhone.getCUserProfileHandler().getCUserProfile();
	if ((cUserProfile) && (cUserProfile->getUserProfile().getActivePhoneLine())) {
                Config & config = ConfigManager::getInstance().getCurrentConfig();
                std::string testnumber = config.getSipAudioTestCall ();
		cUserProfile->getUserProfile().getActivePhoneLine()->makeCall(testnumber);
		QtWengoPhone* qWengoPhone = QtAudioSettings::_cWengoPhone._qtWengoPhone;//Modify By LZY 2010-09-28
		qWengoPhone->getWidget()->raise();
	}
}

void QtAudioSettings::testOutputDevice() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	Sound* testSound = new Sound(config.getAudioCallClosedFile());
	AudioDevice device = getAudioDeviceFromComboBox(_ui->outputDeviceComboBox, AudioDeviceManager::getInstance().getOutputDeviceList());
	testSound->setWaveOutDevice(device);
	//Play the sound 4 times
	testSound->setLoops(4);
	testSound->play();
}

/* zhenHua.sun 2010-08-01
void QtAudioSettings::testRingingDevice() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	Sound* testSound = new Sound(config.getAudioCallClosedFile());
	AudioDevice device = getAudioDeviceFromComboBox(_ui->ringingDeviceComboBox, AudioDeviceManager::getInstance().getOutputDeviceList());
	testSound->setWaveOutDevice(device);
	//Play the sound 4 times
	testSound->setLoops(4);
	testSound->play();
}

void QtAudioSettings::AdvPressed() {
	if (_ui->AdvGroupBox->isVisible()) {
		_ui->AdvGroupBox->setVisible(false);
		_ui->AdvButton->setText(tr("Advanced") + " >>");
	} else {
		_ui->AdvGroupBox->setVisible(true);
		_ui->AdvButton->setText(tr("Advanced") + " <<");
	}
}

void QtAudioSettings::UpPressed() {

	//extracts current Item
	int currentrow = _ui->audioCodecListWidget->currentRow();

	//if an item is selected
	if (currentrow < 0) {
		return;
	}

	QListWidgetItem * mover = _ui->audioCodecListWidget->takeItem(currentrow);

	//inserts it to its new place
	 _ui->audioCodecListWidget->insertItem(currentrow - 1,mover);

	//sets focus on mover
	_ui->audioCodecListWidget->setCurrentItem(mover);
}

void QtAudioSettings::DownPressed() {

	//extracts current Item
	int currentrow = _ui->audioCodecListWidget->currentRow();

	//if an item is selected
	if (currentrow < 0) {
		return;
	}

	QListWidgetItem * mover = _ui->audioCodecListWidget->takeItem(currentrow);

	//inserts it to its new place
	 _ui->audioCodecListWidget->insertItem(currentrow + 1,mover);

	//sets focus on mover
	_ui->audioCodecListWidget->setCurrentItem(mover);
}

void QtAudioSettings::ResetPressed() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	//resets saved audio codec list
	config.resetToDefaultValue(Config::AUDIO_CODEC_LIST_KEY);

	fillAudioCodecList();
}

void QtAudioSettings::fillAudioCodecList() {
	Config & config = ConfigManager::getInstance().getCurrentConfig();

	//resets displayed audio codec list
	StringList audioCodecList = config.getAudioCodecList();
	_ui->audioCodecListWidget->clear();
	for (StringList::const_iterator it = audioCodecList.begin(); it != audioCodecList.end(); ++it) {
		QString audioCodec = QString(it->c_str());
		// HACK: PHAPI_SPEEXWB_REPLACES_G726WB_HACK
		if (audioCodec == "G726-64wb/16000") {
			audioCodec = "SPEEX/16000";
		}
		////
		_ui->audioCodecListWidget->addItem(audioCodec);
	}
	////
}
*/
void QtAudioSettings::saveButtonClicked()
{
	saveConfig();
}

void QtAudioSettings::initVolumeSlider(QSlider* slider) {
	Config & config = ConfigManager::getInstance().getCurrentConfig();
	StringList deviceId;
	if (slider == _ui->_outputVolumeSlider) {
		deviceId = config.getAudioOutputDeviceId();
	} else {
		deviceId = config.getAudioInputDeviceId();
	}
	AudioDevice audioDevice(deviceId);
	VolumeControl volumeControl(audioDevice);

	slider->blockSignals(true);
	slider->setValue(volumeControl.getLevel());
	slider->blockSignals(false);
}

void QtAudioSettings::setVolume(int value) {
	AudioDevice device;
	Config & config = ConfigManager::getInstance().getCurrentConfig();
	StringList deviceId;
	if (sender() == _ui->_outputVolumeSlider) {
		device = getAudioDeviceFromComboBox(_ui->outputDeviceComboBox, AudioDeviceManager::getInstance().getOutputDeviceList());
		//deviceId = config.getAudioOutputDeviceId();
	} else {
		device = getAudioDeviceFromComboBox(_ui->inputDeviceComboBox, AudioDeviceManager::getInstance().getInputDeviceList());
		//deviceId = config.getAudioInputDeviceId();
	}
	//AudioDevice audioDevice(deviceId);
	AudioDevice audioDevice(device.getData());
	VolumeControl volumeControl(audioDevice);
	volumeControl.setLevel(value);

	//// FIXME: Remove this once/if the AudioDevice gets capable of notifying us
	//// of volume changes (from us and from the outside world).
	//if (sender() == _outputVolumeSlider) {
	//	updateAudioOutputUi();
	//} else {
	//	updateAudioInputUi();
	//}
}

void QtAudioSettings::configButtonClicked()
{
	readConfig();
}

//-------Add By LZY 2010-10-05-------
/*
 * 响应SetVolume动作的Signal
 * @param int Value,音量值
 * @param char Type,音量方向 1-扬声器_out 0-麦克风_in
 * @return void
 */
void QtAudioSettings::TeleSetVolumeCommand(int Value,char Type)
{
	Config & config = ConfigManager::getInstance().getCurrentConfig();
	StringList deviceId;
	QSlider* Slider=NULL;
	if (Type==1)//扬声器 out
	{
		deviceId = config.getAudioOutputDeviceId();
		Slider=QtAudioSettings::_ui->_outputVolumeSlider;
	}
	else//麦克风 in
	{
		deviceId = config.getAudioInputDeviceId();
		Slider=QtAudioSettings::_ui->_inputVolumeSlider;
	}
	AudioDevice audioDevice(deviceId);
	VolumeControl volumeControl(audioDevice);
	volumeControl.setLevel(Value);
	Slider->blockSignals(true);
	Slider->setValue(Value);
	Slider->blockSignals(false);
}