# Visual Studio 2022 C++ Gameplay Ability System Text RPG

![](https://velog.velcdn.com/images/gwakgh/post/e46fec95-f243-44bb-a03e-90eb6fd11b68/image.png)
![](https://velog.velcdn.com/images/gwakgh/post/c0aa54e2-e2bc-4ef9-af15-a8c7674ce916/image.png)
![](https://velog.velcdn.com/images/gwakgh/post/3e10577b-f6ee-4cbc-9bd9-2a1ad4a3fa5e/image.png)
![](https://velog.velcdn.com/images/gwakgh/post/864b1d8c-4a86-4401-bb85-059a5ff9c828/image.png)

<br/>

# 🎮 콘솔 기반 텍스트 RPG 게임

언리얼 엔진의 **GAS (Gameplay Ability System)** 구조를 참고하여 Ability, Effect, Attribute 기반 전투 시스템을 구현하고
필드를 돌아다니며 랜덤 확률로 등장하는 몬스터를 잡아 성장하여 보스를 잡는 것이 목적인 게임

<br/>

# 🧱 프로젝트 구조
```
CH2-TextRPGProject/
├── 📂 Actors/
│   ├── 📂 Enemys/
│   │   ├── Boss.*                 # 보스 몬스터 클래스(Enemy)
│   │   ├── Goblin.*              # 고블린 몬스터 클래스(Enemy)
│   │   └── Enemy.*               # Enemy 베이스 클래스(Actor)
│   ├── NPC.*                     # NPC 클래스(Actor)
│   └── Player.*                  # 플레이어 클래스(Actor)
│
├── 📂 Framework/
│   ├── AbilitySystemComponent.*  # 스킬/효과 처리 시스템
│   ├── AttributeSet.*            # 능력치 정의 (HP, 공격력 등)
│   ├── Actor.*                   # Actor 베이스 클래스
│   ├── GameplayAbility.*         # 능력(스킬) 베이스 구조
│   ├── GameplayEffect.h          # 스킬 효과 정의 (버프/디버프 등)
│   └── ItemBase.*                # 모든 아이템의 기반 클래스
│
├── 📂 Items/
│   ├── HealthPotion.*            # 회복 아이템(ItemBase)
│   └── InventoryComponent.*      # 인벤토리 기능 컴포넌트
│
├── 📂 Maps/
│   └── Field.*                   # 필드(맵) 클래스
│
├── 📂 System/
│   ├── FieldState.*              # 필드 상태 관리(GameStateBase)
│   ├── Game.*                    # 메인 게임 루프/컨트롤
│   ├── InventoryState.*          # 인벤토리 상태 관리(GameStateBase)
│   └── MainMenuState.*           # 메인 메뉴 상태(GameStateBase)
│
├── 📂 Skills/
│   └── BasicAttack.*             # 기본 공격 스킬(GameplayAbility)
│
├── 📂 Utils/
│   ├── BattleManager.*           # 전투 처리/연출 관리
│   ├── ConsoleUtils.*            # 콘솔 UI, 입력, 난수 처리
│   └── DamageUtils.*             # 데미지 계산 및 처리 유틸
│
├── GameStateBase.h               # 상태 베이스 클래스
└── Main.cpp                      # 프로그램 진입점

```

<br/>

# 🎮 시스템 특징

- ✅ GAS (Ability/Effect/Attribute) 구조 직현

- ✅ 콘솔 UI 기반 메뉴, 체력 바, 전투 메시지 출력

- ✅ OOP 기반 확장 가능한 캐릭터/스킬/아이템 시스템


<br/>

# 👊 캐릭터 특성 (AttributeSet)

- **Strength**: **힘** 특성. 물리데미지 연산과 `MaxHealth` 에 영향
- **Intelligence**: **지능** 특성. 마법데미지 연산과 `MaxMana` 에 영향
- **Agility**: **민첩** 특성. 물리/마법데미지 연산 중 명중률에 영향
- DefensePower: `Character` 고유의 물리방어력
- MagicResistance: `Character` 고유의 마법저항력
- Health
- Mana
- Level
- Experience
- ExpToNextLevel
- bIsDefending: 방어 상태 여부

<br/>

# 업데이트 로그
- **250617**: 프로그램 구상 (클래스 구조, 전투화면 및 로직, CMD UI 생성)
- **250617**: 최초 commit (필드, Enemy, 메인메뉴 추가)
