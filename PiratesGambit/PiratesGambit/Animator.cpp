#include "Animator.h"

void Animator::AnimateSprite(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, int _colAmt, int _rowNum, float _dt)
{
	const float frameDuration = 0.1f;

	_state.elapsedTime += _dt / 1000.0f;

	_animationComplete = false;

	if (_state.elapsedTime >= frameDuration)
	{
		_state.currentFrame++;
		if (_state.currentFrame > _colAmt - 1)
		{
			_state.currentFrame = 0;
			_animationComplete = true;
		}
		_state.elapsedTime = 0;
	}
	int col = _state.currentFrame % _colAmt;
	int row = _rowNum;

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	_sprite.setTextureRect(rectSourceSprite);
}

void Animator::AnimateShoot(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete , bool& _bulletFrame, int _bulletFrameNumber, int _colAmt, int _rowNum, float _dt)
{
	const float frameDuration = 0.1f;

	_state.elapsedTime += _dt * 0.001;

	_animationComplete = false;

	if (_state.elapsedTime >= frameDuration)
	{
		_state.currentFrame++;
		if(_state.currentFrame == _bulletFrameNumber)
		{
			_bulletFrame = true;
		}
		if (_state.currentFrame > _colAmt - 1)
		{
			_state.currentFrame = 0;
			_animationComplete = true;
		}
		_state.elapsedTime = 0;
	}
	int col = _state.currentFrame % _colAmt;
	int row = _rowNum;

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	_sprite.setTextureRect(rectSourceSprite);
}

void Animator::AnimateDeath(sf::Sprite& _sprite, int _colNum, int _rowNum)
{
	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = _colNum * rectSourceSprite.width;
	rectSourceSprite.top = _rowNum * rectSourceSprite.height;
	_sprite.setTextureRect(rectSourceSprite);
}

void Animator::AnimateParticle(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, int _colNum, int _rowNum, int _width, int _height, float _dt)
{
	const float frameDuration = 0.03f;

	_state.elapsedTime += _dt * 0.001;

	if (_state.elapsedTime >= frameDuration)
	{
		_state.currentFrame++;
		if (_state.currentFrame > _colNum - 1)
		{
			_animationComplete = true;
		}
		_state.elapsedTime = 0;
	}
	int col = _state.currentFrame % _colNum;
	int row = _rowNum;

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = _height;
	rectSourceSprite.width = _width;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	_sprite.setTextureRect(rectSourceSprite);
}
