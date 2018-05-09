#include <string>
#include "XLibrary11.hpp"
using namespace std;
using namespace XLibrary11;

int MAIN()
{
	const float ballSpeed = 5.0f;
	const float playerSpeed = 5.0f;

	Camera camera;
	camera.color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

	Sprite ball(L"ball.png");
	Float3 ballVelocity(ballSpeed, 0.0f, 0.0f);

	Sprite player(L"ball.png");
	player.scale.y = 5.0f;

	Float3 player1Position(-300.0f, 0.0f, 0.0f);
	Float3 player2Position(300.0f, 0.0f, 0.0f);
	int player1Score = 0;
	int player2Score = 0;

	Text player1ScoreText(L"0", 10.0f);
	player1ScoreText.position = Float3(-100.0f, 200.0f, 0.0f);
	player1ScoreText.scale = 10.0f;
	player1ScoreText.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	Text player2ScoreText(L"0", 10.0f);
	player2ScoreText.position = Float3(100.0f, 200.0f, 0.0f);
	player2ScoreText.scale = 10.0f;
	player2ScoreText.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	Sound hitSound(L"hit.wav");
	Sound pointSound(L"point.wav");

	while (App::Refresh())
	{
		camera.Update();

		ball.position += ballVelocity;

		if (ball.position.y > App::GetWindowSize().y / 2.0f)
		{
			ballVelocity.y = -fabsf(ballVelocity.y);
			hitSound.Play();
		}
		if (ball.position.y < -App::GetWindowSize().y / 2.0f)
		{
			ballVelocity.y = fabsf(ballVelocity.y);
			hitSound.Play();
		}

		if (ball.position.x > App::GetWindowSize().x / 2.0f)
		{
			player1Score++;
			player1ScoreText.Create(to_wstring(player1Score).c_str(), 10.0f);
			ball.position = Float3(0.0f, 0.0f, 0.0f);
			ballVelocity.x = -ballVelocity.x;
			ballVelocity.y = 0.0f;
			pointSound.Play();
		}
		if (ball.position.x < -App::GetWindowSize().x / 2.0f)
		{
			player2Score++;
			player2ScoreText.Create(to_wstring(player2Score).c_str(), 10.0f);
			ball.position = Float3(0.0f, 0.0f, 0.0f);
			ballVelocity.x = -ballVelocity.x;
			ballVelocity.y = 0.0f;
			pointSound.Play();
		}

		ball.Draw();

		if (App::GetKey('R'))
		{
			player1Position.y += playerSpeed;
		}
		if (App::GetKey('F'))
		{
			player1Position.y -= playerSpeed;
		}

		if (player1Position.y > App::GetWindowSize().y / 2.0f)
		{
			player1Position.y = App::GetWindowSize().y / 2.0f;
		}
		if (player1Position.y < -App::GetWindowSize().y / 2.0f)
		{
			player1Position.y = -App::GetWindowSize().y / 2.0f;
		}

		float hitRangeX = (player.GetSize().x * player.scale.x + ball.GetSize().x) / 2.0f;
		float hitRangeY = (player.GetSize().y * player.scale.y + ball.GetSize().y) / 2.0f;

		if (player1Position.x - hitRangeX < ball.position.x &&
			player1Position.x + hitRangeX > ball.position.x &&
			player1Position.y - hitRangeY < ball.position.y &&
			player1Position.y + hitRangeY > ball.position.y)
		{
			ballVelocity.x = fabsf(ballSpeed);
			ballVelocity.y = (ball.position.y - player1Position.y) * 0.2f;
			hitSound.Play();
		}

		player.position = player1Position;
		player.Draw();

		if (App::GetKey('U'))
		{
			player2Position.y += playerSpeed;
		}
		if (App::GetKey('J'))
		{
			player2Position.y -= playerSpeed;
		}

		if (player2Position.y > App::GetWindowSize().y / 2.0f)
		{
			player2Position.y = App::GetWindowSize().y / 2.0f;
		}
		if (player2Position.y < -App::GetWindowSize().y / 2.0f)
		{
			player2Position.y = -App::GetWindowSize().y / 2.0f;
		}

		if (player2Position.x - hitRangeX < ball.position.x &&
			player2Position.x + hitRangeX > ball.position.x &&
			player2Position.y - hitRangeY < ball.position.y &&
			player2Position.y + hitRangeY > ball.position.y)
		{
			ballVelocity.x = -fabsf(ballSpeed);
			ballVelocity.y = (ball.position.y - player2Position.y) * 0.2f;
			hitSound.Play();
		}

		player.position = player2Position;
		player.Draw();

		player1ScoreText.Draw();
		player2ScoreText.Draw();
	}

	return 0;
}
