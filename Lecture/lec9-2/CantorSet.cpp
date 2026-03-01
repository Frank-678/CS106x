// 也是有难度的的window.drawLine(x, y, x + len, y);这一步理解作为参数的变量是变化的

void CantorSet(GWindow& window, int x, int y, int len, int levels) {
    if (levels >= 1) {  // 实际思路是从上到下（一级到levels级，画的次数就是levels减少到1）
        window.drawLine(x, y, x + len, y); // level x
        CantorSet(window, x, y + 20, len / 3, levels - 1);
        CantorSet(window, x + len * 2 / 3, y + 20, len / 3, levels - 1); // level x + 1
    }

    // base case
    // nothing to do (0)
}