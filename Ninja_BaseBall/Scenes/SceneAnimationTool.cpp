#include "pch.h"
#include "SceneAnimationTool.h"
#include "Button.h"
#include "SpriteGo.h"
#include "InputField.h"
#include "TextGo.h"
#include "PreviewCharacter.h"

SceneAnimationTool::SceneAnimationTool(SceneIDs id)
	: Scene(id)
{
	windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
}

void SceneAnimationTool::Init()
{
	font = *FONT_MANAGER.GetResource("fonts/strikers1945.ttf");

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	worldView.setViewport(sf::FloatRect(0.2f, 0.2f, 0.6f, 0.6f));
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	previewCharacter = new PreviewCharacter();
	AddGameObject(previewCharacter, Layers::Ui);

	buttonLoadAtlas = new Button(Button::ButtonIdentifier::loadAtlas);
	buttonLoadAtlas->SetStringValue(atlasPath);
	buttonLoadAtlas->SetButton({ 60.f,30.f }, { windowSize.x * 0.1f, windowSize.y * 0.2f }, sf::Color::White, Origins::MC);
	buttonLoadAtlas->SetButtonText(font, "Load\nSprite Atlas", 12.f, sf::Color::Black, { windowSize.x * 0.1f, windowSize.y * 0.2f }, Origins::MC);
	AddGameObject(buttonLoadAtlas, Layers::Ui);

	spriteSheet = new SpriteGo("spritesheet");
	spriteSheet->Init();

	textFPS = new TextGo("textfps");
	textFPS->Set(font, "FPS", 20, sf::Color::White);
	textFPS->SetPosition(windowSize.x * 0.1f, windowSize.y * 0.25f);
	textFPS->SetOrigin(Origins::MR);
	AddGameObject(textFPS, Layers::Ui);

	textGuidline = new TextGo("textguidline");
	textGuidline->Set(font, "Select Frame Bound", 20, sf::Color::White);
	textGuidline->SetPosition(windowSize.x * 0.2f, windowSize.y * 0.18f);
	textGuidline->SetOrigin(Origins::BL);
	AddGameObject(textGuidline, Layers::Ui);

	inputfieldFPS = new InputField("inputfieldfps");
	inputfieldFPS->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.27f);
	inputfieldFPS->SetOrigin(Origins::ML);
	AddGameObject(inputfieldFPS, Layers::Ui);

	// TODO : Auto Slice ���
	inputfieldRow = new InputField("inputfieldfps");
	inputfieldRow->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.27f);
	inputfieldRow->SetOrigin(Origins::ML);
	AddGameObject(inputfieldRow, Layers::Ui);

	inputfieldCol = new InputField("inputfieldfps");
	inputfieldCol->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.27f);
	inputfieldCol->SetOrigin(Origins::ML);
	AddGameObject(inputfieldFPS, Layers::Ui);

	buttonStop = new Button(Button::ButtonIdentifier::stop, "buttonstop");
	buttonStop->SetButton({ 30.f,30.f }, { windowSize.x * 0.1f, windowSize.y * 0.5f }, sf::Color::White, Origins::MC);
	buttonStop->SetButtonText(font, "Stop", 12.f, sf::Color::Black, { windowSize.x * 0.1f, windowSize.y * 0.5f }, Origins::MC);
	AddGameObject(buttonStop, Layers::Ui);

	buttonPlay = new Button(Button::ButtonIdentifier::play, "buttonplay");
	buttonPlay->SetButton({ 30.f,30.f }, { windowSize.x * 0.15f, windowSize.y * 0.5f }, sf::Color::White, Origins::MC);
	buttonPlay->SetButtonText(font, "Play", 12.f, sf::Color::Black, { windowSize.x * 0.15f, windowSize.y * 0.5f }, Origins::MC);
	AddGameObject(buttonPlay, Layers::Ui);

	buttonSaveAnimation = new Button(Button::ButtonIdentifier::save, "buttonsave");
	buttonSaveAnimation->SetButton({ 80.f,40.f }, { windowSize.x * 0.75f, windowSize.y * 0.85f }, sf::Color::White, Origins::MC);
	buttonSaveAnimation->SetButtonText(font, "Save\nAnimation", 15.f, sf::Color::Black, { windowSize.x * 0.75f, windowSize.y * 0.85f }, Origins::MC);
	AddGameObject(buttonSaveAnimation, Layers::Ui);

	buttonAutoSlice = new Button(Button::ButtonIdentifier::autoslice, "buttonautoslice");
	buttonAutoSlice->SetButton({ 80.f,40.f }, { windowSize.x * 0.11f, windowSize.y * 0.35f }, sf::Color::White, Origins::MC);
	buttonAutoSlice->SetButtonText(font, "Auto Slice", 15.f, sf::Color::Black, { windowSize.x * 0.11f, windowSize.y * 0.35f }, Origins::MC);
	AddGameObject(buttonAutoSlice, Layers::Ui);


	buttonLoadCsv = new Button(Button::ButtonIdentifier::loadcsv, "buttonloadcsv");
	buttonLoadCsv->SetButton({ 80.f,40.f }, { windowSize.x * 0.11f, windowSize.y * 0.1f }, sf::Color::White, Origins::MC);
	buttonLoadCsv->SetButtonText(font, "Load CSV", 15.f, sf::Color::Black, { windowSize.x * 0.11f, windowSize.y * 0.1f }, Origins::MC);
	AddGameObject(buttonLoadCsv, Layers::Ui);


	editorBorder.setOutlineColor(sf::Color::Red);
	editorBorder.setFillColor(sf::Color::Transparent);
	editorBorder.setOutlineThickness(2.f);
	editorBorder.setPosition(windowSize.x * 0.2f, windowSize.y * 0.2f);
	editorBorder.setSize({ windowSize.x * 0.6f, windowSize.y * 0.6f });

	textureBorder.setOutlineColor(sf::Color::Cyan);
	textureBorder.setFillColor(sf::Color::Transparent);
	textureBorder.setOutlineThickness(5.f);

	for (int i = 0; i < loopButtonsText.size(); ++i)
	{
		loopButtons.push_back(new Button(Button::ButtonIdentifier::loop, "loopbutton" + std::to_string(i)));

		loopButtons[i]->SetButton({ 80.f,40.f }, { windowSize.x * (0.4f + 0.15f * i), windowSize.y * 0.15f }, sf::Color::White, Origins::MC);
		loopButtons[i]->SetButtonText(font, loopButtonsText[i], 15.f, sf::Color::Black, { windowSize.x * (0.4f + 0.15f * i), windowSize.y * 0.15f }, Origins::MC);
		AddGameObject(loopButtons[i], Layers::Ui);
	}
	for (int i = 0; i < originButtonsText.size(); ++i)
	{
		originButtons.push_back(new Button(Button::ButtonIdentifier::pivot, "originbutton" + std::to_string(i)));

		originButtons[i]->SetButton({ 80.f,30.f }, { windowSize.x * 0.95f, windowSize.y * (0.2f + 0.08f * i) }, sf::Color::White, Origins::MC);
		originButtons[i]->SetButtonText(font, originButtonsText[i], 15.f, sf::Color::Black, { windowSize.x * 0.95f, windowSize.y * (0.2f + 0.08f * i) }, Origins::MC);
		AddGameObject(originButtons[i], Layers::Ui);
	}

	Scene::Init();
}

void SceneAnimationTool::Release()
{
	Scene::Release();
}

void SceneAnimationTool::Reset()
{
}

void SceneAnimationTool::Enter()
{
	Scene::Enter();
	status = GameStatus::Game;
}

void SceneAnimationTool::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);

	Scene::Exit();
}

void SceneAnimationTool::Update(float dt)
{
	Scene::Update(dt);
	SetStatus(status);

	switch (status)
	{
	case GameStatus::Awake:
		UpdateAwake(dt);
		break;
	case GameStatus::Game:
		UpdateGame(dt);
		break;
	case GameStatus::GameOver:
		UpdateGameover(dt);
		break;
	case GameStatus::Pause:
		UpdatePause(dt);
		break;
	default:
		break;
	}
}

void SceneAnimationTool::UpdateEvent(const sf::Event& event)
{
	Scene::UpdateEvent(event);
	switch (event.type)
	{
	case  sf::Event::MouseWheelScrolled:
	{
		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			float zoomAmount = 0.1f;
			if (event.mouseWheelScroll.delta > 0)
			{
				worldView.zoom(1.f - zoomAmount);
			}
			else
			{
				worldView.zoom(1.f + zoomAmount);
			}
		}
	}
	break;
	case sf::Event::MouseButtonPressed:
	{
		if (event.mouseButton.button == sf::Mouse::Left && !isCustomPivot)
		{
			sf::Vector2f mouseWorldPos = ScreenToWorld((sf::Vector2i)InputManager::GetMousePos());
			if (IsWithinWorldView(mouseWorldPos))
			{
				isLeftDragging = true;
				leftDragStartPos = mouseWorldPos;
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			isRightDragging = true;
			rightDragStartPos = ScreenToWorld((sf::Vector2i)InputManager::GetMousePos());
			lastMousePos = rightDragStartPos;
		}
	}
	break;
	case sf::Event::MouseButtonReleased:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (isLeftDragging && isAtlasPath && !isCustomPivot)
			{
				isLeftDragging = false;
				sf::Vector2f endPos = ScreenToWorld((sf::Vector2i)InputManager::GetMousePos());
				if (IsWithinWorldView(endPos))
				{
					leftDragStartPos.x = std::max(0.f, leftDragStartPos.x);
					leftDragStartPos.y = std::max(0.f, leftDragStartPos.y);

					sf::Vector2f RightBottomPos = endPos - leftDragStartPos;

					sf::FloatRect selectedArea(leftDragStartPos, RightBottomPos);

					selectedAreas.push_back(selectedArea);

					std::cout << selectedArea.left
						<< " : " << selectedArea.top
						<< " : " << selectedArea.width
						<< " : " << selectedArea.height << std::endl;
				}
			}

			if (isCustomPivot)
			{
				textGuidline->SetText(guidlines[0]);
				sf::Vector2f lastRect = { selectedAreas[selectedAreas.size() - 1].left, selectedAreas[selectedAreas.size() - 1].top };
				sf::Vector2f customPivot = (ScreenToWorld((sf::Vector2i)InputManager::GetMousePos()) - lastRect);

				if (customPivot.y > selectedAreas[selectedAreas.size() - 1].top + selectedAreas[selectedAreas.size() - 1].height)
				{
					customPivot.y = selectedAreas[selectedAreas.size() - 1].top + selectedAreas[selectedAreas.size() - 1].height;
				}

				customPivots.push_back(customPivot);

				std::cout << "Custom Pivot, Selected Pivot : " << customPivot.x << " : " << customPivot.y << std::endl;
				isCustomPivot = false;
			}
			else
			{
				textGuidline->SetText(guidlines[1]);
			}
		}
			
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			isRightDragging = false;
		}
	}
	break;

	case sf::Event::MouseMoved:
	{
		if (isLeftDragging)
		{
			currentMousePos = ScreenToWorld((sf::Vector2i)InputManager::GetMousePos());
		}
		if (isRightDragging)
		{
			// TODO : ���콺 ��ġ�� sf::Vector2f�� �����ϴ� ���
			currentMousePos = ScreenToWorld((sf::Vector2i)InputManager::GetMousePos());
			sf::Vector2f delta = lastMousePos - currentMousePos;
			worldView.move(delta);
			lastMousePos = currentMousePos;
		}
		break;
	}
	}
}

void SceneAnimationTool::UpdateAwake(float dt)
{
}

void SceneAnimationTool::UpdateGame(float dt)
{
	if (atlasPath != L"" && !isAtlasPath)
	{
		isAtlasPath = true;
		spriteSheet->SetTexture(Utils::MyString::WideStringToString(atlasPath));
		spriteSheet->SetPosition({ 0,0 });
		spriteSheet->SetOrigin(Origins::TL);


		if (!isLoadedFromCsv)
		{
			selectedAreas.clear();
			selectedAreasPivot.clear();
			selectedLoopType = AnimationLoopType::Single; // �⺻ ��
			customPivots.clear();
		}

		previewCharacter->GetAnimator().ClearFrames();

		textureBorder.setPosition(0, 0);
		textureBorder.setSize((sf::Vector2f)spriteSheet->GetTexture()->getSize());

		if (firstTextureLoad)
		{
			firstTextureLoad = false;
			AddGameObject(spriteSheet);
		}
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Delete))
	{
		if (selectedAreas.empty()) return;
		// ������ ���õ� ���� ����
		std::cout << "selected Area deleted!" << std::endl;
		if (selectedAreas.size() > selectedAreasPivot.size())
		{
			selectedAreas.erase(selectedAreas.end() - 1);
		}
		else if (selectedAreas.size() == selectedAreasPivot.size())
		{
			selectedAreas.erase(selectedAreas.end() - 1);
			selectedAreasPivot.erase(selectedAreasPivot.end() - 1);
			customPivots.erase(customPivots.end() - 1);
			std::cout << "selected Pivot deleted!" << std::endl;
		}
	}
}

void SceneAnimationTool::UpdateGameover(float dt)
{

}

void SceneAnimationTool::UpdatePause(float dt)
{

}

void SceneAnimationTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//TEST
	const sf::View& saveView = window.getView();
	window.setView(uiView);
	window.draw(editorBorder);
	window.setView(worldView);
	window.draw(textureBorder);
	window.setView(saveView);

	if (isLeftDragging)
	{
		sf::RectangleShape dragRect;
		dragRect.setPosition(leftDragStartPos);
		sf::Vector2f size = currentMousePos - leftDragStartPos;
		dragRect.setSize(size);
		dragRect.setFillColor(sf::Color::Transparent);
		dragRect.setOutlineColor(sf::Color::Green);
		dragRect.setOutlineThickness(1.0f);
		window.setView(worldView);
		window.draw(dragRect);
	}

	for (const auto& area : selectedAreas)
	{
		sf::RectangleShape rectangle;
		rectangle.setPosition(sf::Vector2f(area.left, area.top));
		rectangle.setSize(sf::Vector2f(area.width, area.height));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color::Green);
		rectangle.setOutlineThickness(1.0f);

		window.setView(worldView);
		window.draw(rectangle);
	}

	for (int i = 0; i < customPivots.size(); ++i)
	{
		if (customPivots[i] == sf::Vector2f(0, 0)) continue;

		sf::RectangleShape pivotImg;
		sf::Vector2f area = { selectedAreas[i].left , selectedAreas[i].top };

		pivotImg.setFillColor(sf::Color::Green);
		pivotImg.setSize({ 10,10 });
		pivotImg.setPosition(area + customPivots[i]);
		pivotImg.setOrigin({5,5});

		window.setView(worldView);
		window.draw(pivotImg);
	}
}


void SceneAnimationTool::SetAtlasPath(std::wstring& str)
{
	atlasPath = str;
	std::cout << Utils::MyString::WideStringToString(str) << std::endl;
}

void SceneAnimationTool::SetFPS(const std::wstring& fps)
{
	inputfieldFPS->SetText(Utils::MyString::WideStringToString(fps));
}

void SceneAnimationTool::SetLoopType(const AnimationLoopType looptype)
{
	selectedLoopType = looptype;
}

void SceneAnimationTool::SetStatus(GameStatus newStatus)
{
	GameStatus prevStatus = status;

	status = newStatus;

	switch (status)
	{
	case GameStatus::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case GameStatus::Game:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case GameStatus::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case GameStatus::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

bool SceneAnimationTool::IsWithinWorldView(const sf::Vector2f& point)
{
	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
	return viewBounds.contains(point);
}