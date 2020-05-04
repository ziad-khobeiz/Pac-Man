#include "Animator.h"

#include <iostream>

Animator::Animator() : playing(0), curFrame(0), duration(sf::Time::Zero), repeat(0), timeBuffer(sf::Time::Zero)
{
}


Animator::~Animator()
{
}

void Animator::addFrame(sf::IntRect picture) {

	frames.push_back(picture);

}

bool Animator::isPlaying() {

	return playing;

}

void Animator::setAnimation(sf::Time animationDuration, bool loop) {

	duration = animationDuration;
	repeat = loop;
	playing = 1;

}

void Animator::update(sf::Time delta) {

	if (!playing) return;

	timeBuffer += delta;

	sf::Time timePerFrame = duration / float(frames.size());

	while (timeBuffer >= timePerFrame) {

		timeBuffer -= timePerFrame;
		++curFrame;

		if (curFrame == frames.size()) {

			if (!repeat) playing = 0;

			curFrame = 0;

		}

	}

}

void Animator::animate(sf::Sprite &sprite) {

	sprite.setTextureRect(frames[curFrame]);

}