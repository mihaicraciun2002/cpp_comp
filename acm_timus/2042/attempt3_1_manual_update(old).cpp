
inline void manualUpdate(const int& l, const int& r)  {
	prepareManacherString(l, r);
	int newL = l * 2 - 1;
	int newR = r * 2 + 1;
	memset(dManacher + newL, 0, (newR - newL + 1) * sizeof(int));
	for(int i = newL;i <= newR;i++)
		assert(dManacher[i] == 0);
	int bestIndex = newL;
	int bestRange = -1;
	for(int index = newL;index <= newR;index++)  {
		if(bestIndex + bestRange >= index)  {
			dManacher[index] = std::min(dManacher[2 * bestIndex - index],
				(bestIndex - index + bestRange));
		}
		while(index + dManacher[index] + 1 <= newR && index - dManacher[index] - 1 >= newL &&
			sManacher[index + dManacher[index] + 1] == sManacher[index - dManacher[index] - 1])
			dManacher[index]++;
		if(index + dManacher[index] > bestIndex + bestRange)  {
			bestIndex = index;
			bestRange = dManacher[index];
		}
	}
	long long ans = 0;
	std::unordered_map <int, long long> dpMem;
	for(int i = newL;i <= newR;i++)  {
		if(i % 2 == 0)  {
			int maxDim = (dManacher[i] + 1) / 2 * 2 - 1;
			maxDim = std::min(maxDim, k + (k % 2 - 1));
			maxDim = (maxDim + 1) / 2;
			dpMem[i / 2] += maxDim;
			ans += 1LL * maxDim;
		}else{
			int maxDim = (dManacher[i] + 1) / 2 * 2;
			maxDim = std::min(maxDim, k - k % 2);
			maxDim = maxDim / 2;
			dpMem[i / 2] += maxDim;
			ans += 1LL * maxDim;
		}
	}
	for(const auto& x : dpMem)
		dp.update(x.first, x.first, x.second);
}