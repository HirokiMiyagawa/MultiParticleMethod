/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	Console.hpp
 * @brief	コンソール上に行った動作を表示する
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

/**
 * @brief		今どんな動作が行われたかコンソールに表示する
 * @param[in]	int i switch分に使用
 * @note
 * @details		表示内容は
 * コンストラクタの起動
 * デコンストラクタの起動
 * simulateMethodの起動
 * 初期座標のセット
 * ポインタのポインタが存在しない
 * 0：コンストラクタを呼び出した
 * 1：デストラクタを呼び出した
 * 2：シミュレーションメソッドの開始
 * 3：setInitialConditionsを呼び出した
 * 4：flagがない
 */
void MultiParticle::console(int i) {
    cout << " "
         << "[  " << FONT_GREEN << "MultiParticle" << ALL_DEFAULT << "  ]";

    switch (i) {
        case 0:
            cout << "Constuctor called...";
            break;

        case 1:
            cout << "Destuctor called...";
            break;

        case 2:
            cout << "simulateMethod called...";
            break;

        case 3:
            cout << "setInitialConditions called...";
            break;

        case 4:
            cout << "flag is not setting.";
            break;

        default:
            break;
    }
    cout << endl;
}
