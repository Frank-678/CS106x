static string generateStory(const string& storyTemplate, const Map<string, string>& data) {
    string result = "";
    for (int i = 0; i < storyTemplate.length(); ++i) {
        if (storyTemplate[i] != '{') {
            result += storyTemplate[i];
        } else {
            // find end
            // and get token
            int m = i + 1;
            string token = "";
            while (storyTemplate[m] != '}') {
                token += storyTemplate[m];
                m++;
            }
            result += data.get(token);
            i = m; // m 此时在}，加上for的++i正好到}后第一个字母
        }
    }

    return result;
}
