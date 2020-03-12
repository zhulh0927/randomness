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

#include "scoreboard_estimator.h"

#include <algorithm>
#include <cmath>

#include "binary_search.h"
#include "boundary.h"
#include "prediction_estimator.h"

using namespace randomness::sp800_90b::estimator;

static const double LogAlpha = log(0.99);

double ScoreboardEstimator::Estimate(const uint8_t* data, size_t len, size_t alph_size) 
{
    sample = data;
    countSamples = len;
    countAlphabets = alph_size;
    
    MakePredictions();

    correct_info_t info = {countAlphabets, maxCorrectRuns, countCorrects, countPredictions};
    PredictionEstimator pe;
    return pe.Estimate(info);
}

void ScoreboardEstimator::MakePredictions()
{
    Initialize();

    for (size_t i = startPredictionIndex; i < countSamples; ++i) {
        UpdatePredictions(i);
        CountCorrectPredictions(i);
        UpdateScoreBoard(i);
    }

    if (maxCorrectRuns < correctRuns) {
        maxCorrectRuns = correctRuns;
    }

    logstream << "countCorrects=" << countCorrects << ", max_run=" << maxCorrectRuns;
}

void ScoreboardEstimator::CountCorrectPredictions(size_t idx)
{
    if (prediction[winner] == sample[idx]) {
        correctRuns += 1;
        countCorrects += 1;

    } else {
        if (maxCorrectRuns < correctRuns) {
            maxCorrectRuns = correctRuns;
        }
        correctRuns = 0;
    }
}

void ScoreboardEstimator::UpdateScoreBoard(size_t idx) 
{
    for (auto i = 0; i < scoreboard.size(); ++i) {
        if (prediction[i] == sample[idx]) {
            scoreboard[i] += 1;

            if (scoreboard[i] >= scoreboard[winner]) {
                winner = i;
            }
        }
    }
}