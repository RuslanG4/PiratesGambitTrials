#include "Animator.h"

void Animator::AnimateSprite(sf::Sprite& _sprite, int _colAmt, int _rowNum)
{
	animateTime++;
	if (animateTime > 8)//8 is the speed at how fast they animate
	{
		currentFrame++;
		if (currentFrame > _colAmt - 1)
		{
			currentFrame = 0;

		}
		animateTime = 0;
	}
	int col = currentFrame % _colAmt;
	int row = _rowNum;

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	_sprite.setTextureRect(rectSourceSprite);
}
