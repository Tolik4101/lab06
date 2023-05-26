## Ход работы
В данной лабораторной работе предлагается разобраться CPack -  инструментом упаковки скомпилированного проекта в платформо-зависимые пакеты и установщики.

### Шаг 1. Создание релиза
Для начала создадим release. В этот раздел, в будущем, будут выкладываться те самые платформозависимые пакеты, откуда их можно будет скачать и установить прямо с github. Воспользуемся готовым расширением ncipollo/release-action, для которого всего лишь надо будет задать необходимые параметры   
```yml
- name: Create Release
  uses: ncipollo/release-action@v1.10.0
  id: create_release
  with:
    draft: false
    prerelease: false
    name: ${{ steps.version.outputs.version }}
    tag: "Packages" # Под каким тэгом выгружать
    body_path: ChangeLog.md
    allowUpdates: true
  env:
    GITHUB_TOKEN: ${{ github.token }}
```

### Шаг 2. Сборка приложения и пакетов
Собираем приложение и пакеты под указанные операционные системы\пакетные менеджеры
```yml
- name: building_artifacts
  shell: bash
  run: |
    sudo apt-get install -y cmake # установка cmake
    sudo apt-get install -y rpm # установка rpm (менеджер пакетов)
    cmake -H. -B_build # сборка приложения
    cmake --build _build --target package # собираем пакеты под указанные системы
```

### Шаг 3. Выгрузка пакетов
Для простоты укажу лишь выгрузку deb пакета. Все остальные делаются абсолютно аналогично. Используем готовый action для выгрузки
```yml
- name: upload deb artifact
  uses: actions/upload-release-asset@v1
  env:
    GITHUB_TOKEN: ${{ github.token }}
  with:
    upload_url: ${{ steps.create_release.outputs.upload_url }} # ссылка на релиз, куда выгрузить
    asset_path: ./_build/banking-0.1.0.0-Linux.deb # указываем, куда выгрузить
    asset_name: banking.deb # локальное название на машине
    asset_content_type: application/apt
```