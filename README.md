# WutheringWaves 🎮

[![시연 영상 미리보기](https://img.youtube.com/vi/BNmhlIee6TE/0.jpg)](https://youtu.be/BNmhlIee6TE)

---

## 팀원
+ 정민수(팀장): 몬스터 / 전투
+ 유호근: 캐릭터
+ 김미진: 인벤토리 / UI

## 제작 기간
06.27.2025 - 07.28.2025

## Stacks

### Development
<div>
<img src="https://img.shields.io/badge/C++-512BD4?style=flat-square&logo=c++&logoColor=white"/>
<img src="https://img.shields.io/badge/Unreal-000000?style=flat-square&logo=unreal&logoColor=white"/>
</div>

### Tools & Communication
<div>
<img src="https://img.shields.io/badge/Notion-000000?style=flat-square&logo=notion&logoColor=white"/>
<img src="https://img.shields.io/badge/Discord-5865F2?style=flat-square&logo=discord&logoColor=white"/>
</div>

## 자료
[PPT](https://drive.google.com/file/d/1MnS2v6If6Yqjyq6sGg8vCqgcCpYp_dq8/view?usp=share_link)

## 주요 기능 ✨

### 1. 무기 인벤토리 시스템

- `FInventoryBase`, `FInventoryWeapon` 구조체를 활용한 인벤토리 데이터 구조 설계.
- 무기 현재 레벨, 돌파 단계(Rank), 스킬 레벨, 소유 캐릭터, 아이콘 이미지 등을 보관. 
- 플레이어 세팅 위젯(PlayerSettingWidget)과 UI 컴포넌트, PlayerController를 통해 인벤토리 데이터를 HUD/UI에 연동.

### 2. 무기 인벤토리 UI

- 무기 리스트, 레벨, 옵션 수치, 희귀도, 장착 상태 등을 한 화면에서 확인 가능한 Weapon Inventory UI 구현. 
- 각 무기 선택 시 캐릭터 정보, 능력치 설명, 무기 상세 정보를 갱신하여 표시.
- 무기 변경 시 캐릭터 스탯 패널이 즉시 갱신되도록 이벤트 연동.

### 3. 정렬 및 필터링 기능

- 희귀도, 레벨 기준 정렬 등 정렬 기준 Enum(`EWeaponSortStandard`)을 통한 무기 정렬 기능 구현.
- `TArray::Sort`와 커스텀 프레디케이트를 사용해 희귀도 or 레벨 순으로 정렬. 
- 정렬 버튼 위젯(WBP Sort Button)에서 Event Dispatcher를 통해 인벤토리 위젯에 정렬/역정렬 요청.

### 4. 캐릭터/무기 연동 HUD

- Player HUD 위젯에서 현재 조작 중인 캐릭터 정보를 받아와 이름, 아이콘, 스킬 아이콘 등을 UI에 표시.
- 인벤토리에서 무기를 교체하면, 캐릭터 스탯 설명 위젯의 수치(공격력, 부옵션 등)가 변경된 무기에 맞게 업데이트.

### 5. 스탯 곡선 및 설명 문자열

- CurveTable을 활용해 스킬 레벨에 따른 스탯 수치를 계산.
- `GetFormattedDescription` 함수를 통해 스탯 이름·수치·중첩 수·지속 시간 등을 치환한 설명 문자열 생성.

## 폴더 및 구조 (개략)

- `Source/`  
  - 인벤토리 데이터 구조 및 정렬 로직(C++) 구현.
- `Content/UI/`  
  - Player HUD, PlayerSettingWidget, Weapon Inventory, 정렬 버튼 위젯 등 UMG 애셋.
- `Content/Characters/`  
  - 캐릭터 스켈레탈 메시 및 SceneCapture2D를 활용한 캐릭터 미리보기 설정.

## 실행 관련 안내 ⚠

- 저장소에 포함된 언리얼 프로젝트는 일부 에셋이 제외되어 있어 바로 실행이 어려울 수 있습니다.
- 실제 동작 화면은 시연 영상과 발표 자료(PPT)를 참고하는 것을 권장합니다.

## 경고
+ 해당 언리얼 파일은 Asset이 빠진 버전으로 정상 구동이 되지 않습니다
+ 깃허브는 언리얼 파일의 Source Code 확인용으로만 사용하시고, 구동은 실행 영상과 PPT를 참고해주시길 바랍니다
