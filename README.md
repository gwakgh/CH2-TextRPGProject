# Visual Studio 2022 C++ Gameplay Ability System


![](https://velog.velcdn.com/images/gwakgh/post/5f54c268-8686-4983-bbb7-59a6d07661f4/image.PNG)

<br/>

# 🎮 콘솔 기반 텍스트 RPG 게임

언리얼 엔진의 **GAS (Gameplay Ability System)** 구조를 참고하여 Ability, Effect, Attribute 기반 전투 시스템을 구현

<br/>

# 🧱 프로젝트 구조
```
ProjectGASTest/
├── 📂 Framework/
│   ├── AbilitySystemComponent.*     # 능력(스킬) 시스템 처리
│   ├── AttributeSet.*               # 캐릭터 능력치 정의 (HP, 공격력 등)
│   ├── Character.*                  # 캐릭터 베이스 클래스
│   ├── GameplayAbility.*            # 스킬 클래스의 기반 구조
│   ├── GameplayEffect.h             # 스킬 효과(버프/디버프) 정의
│   └── BattleManager.*              # 전투 로직 및 상태 머신
│
├── 📂 Skills/
│   ├── Hit.*                        # 일반 공격 스킬 (GameplayAbility)
│   └── MagicClawAbility.*           # 마법 발톱 스킬 (GameplayAbility)
│
├── 📂 Characters/
│   ├── Monster.h                    # 몬스터 클래스 (Character)
│   └── Player.h                     # 플레이어 클래스 (Character)
│
├── 📂 Items/
│   └── HealthPotion.h               # 회복 아이템 (ItemBase)
│
├── ConsoleUtils.*                   # 콘솔 UI 출력 유틸 (drawBox, gotoxy, 난수발생 등)
├── ItemBase.h                       # 아이템 클래스의 베이스
├── main.cpp                         # 진입점 및 게임 루프
```

<br/>

# 🎮 시스템 특징

- ✅ GAS (Ability/Effect/Attribute) 구조 직접 구현

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

<br/>

# 업데이트 로그
- **250617**: 최초 Commit (클래스 구조, 전투화면 및 로직, CMD UI 생성)
