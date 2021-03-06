/**
 * The MIT License
 *
 * Copyright (c) 2020 Ilwoong Jeong (https://github.com/ilwoong)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "mcv_estimator.h"

#include <algorithm>
#include <cmath>
#include <vector>

#include "boundary.h"

using namespace randomness::sp800_90b::estimator;

std::string McvEstimator::Name() const
{
    return "Most Common Value Estimate";
}

double McvEstimator::Estimate()
{
    std::vector<size_t> counts(countAlphabets, 0);

    for (auto i = 0; i < countSamples; ++i) {
        counts[sample[i]] += 1;
    }

    auto max = *std::max_element(counts.begin(), counts.end());
    auto pmax = static_cast<double>(max) / countSamples;

    logstream << "max=" << max << ", pmax=" << pmax;

    return -log2(UpperBoundProbability(pmax, countSamples));
}