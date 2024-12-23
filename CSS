<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Website Analyzer</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        body {
            background: #f0f2f5;
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            padding: 20px;
        }

        .container {
            background: white;
            border-radius: 12px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            width: 100%;
            max-width: 800px;
            padding: 30px;
        }

        .title {
            text-align: center;
            color: #1a1a1a;
            font-size: 2rem;
            margin-bottom: 30px;
        }

        .input-group {
            display: flex;
            gap: 10px;
            margin-bottom: 20px;
        }

        .url-input {
            flex: 1;
            padding: 12px 15px;
            border: 2px solid #e1e1e1;
            border-radius: 8px;
            font-size: 16px;
            transition: border-color 0.3s;
        }

        .url-input:focus {
            outline: none;
            border-color: #007bff;
        }

        .analyze-btn {
            padding: 12px 25px;
            background: #007bff;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            cursor: pointer;
            transition: background 0.3s;
        }

        .analyze-btn:hover {
            background: #0056b3;
        }

        .analyze-btn:disabled {
            background: #cccccc;
            cursor: not-allowed;
        }

        .error {
            background: #ffe6e6;
            border: 1px solid #ff8080;
            color: #cc0000;
            padding: 15px;
            border-radius: 8px;
            margin-bottom: 20px;
            display: none;
        }

        .results {
            display: none;
        }

        .score-card {
            text-align: center;
            margin-bottom: 30px;
        }

        .total-score {
            font-size: 3rem;
            font-weight: bold;
            color: #007bff;
        }

        .score-label {
            color: #666;
            margin-top: 5px;
        }

        .scores-grid {
            display: grid;
            gap: 15px;
            margin-top: 20px;
        }

        .score-item {
            background: #f8f9fa;
            padding: 15px;
            border-radius: 8px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            transition: transform 0.2s;
        }

        .score-item:hover {
            transform: translateY(-2px);
        }

        .category {
            font-weight: 500;
            color: #333;
        }

        .score {
            font-weight: bold;
        }

        .score.good {
            color: #28a745;
        }

        .score.average {
            color: #ffc107;
        }

        .score.poor {
            color: #dc3545;
        }

        .loading {
            display: none;
            text-align: center;
            padding: 20px;
        }

        .loading-spinner {
            border: 4px solid #f3f3f3;
            border-top: 4px solid #007bff;
            border-radius: 50%;
            width: 40px;
            height: 40px;
            animation: spin 1s linear infinite;
            margin: 0 auto 15px;
        }

        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }

        @media (max-width: 600px) {
            .container {
                padding: 20px;
            }

            .input-group {
                flex-direction: column;
            }

            .analyze-btn {
                width: 100%;
            }

            .title {
                font-size: 1.5rem;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1 class="title">Website Analyzer</h1>
        
        <div class="input-group">
            <input 
                type="url" 
                class="url-input" 
                id="url-input"
                placeholder="Enter website URL (e.g., https://example.com)" 
            >
            <button 
                class="analyze-btn" 
                id="analyze-btn"
                onclick="analyzeWebsite()"
            >
                Analyze
            </button>
        </div>

        <div class="error" id="error"></div>

        <div class="loading" id="loading">
            <div class="loading-spinner"></div>
            <div>Analyzing website...</div>
        </div>

        <div class="results" id="results">
            <div class="score-card">
                <div class="total-score">0/10</div>
                <div class="score-label">Overall Score</div>
            </div>
            <div class="scores-grid" id="scores-grid"></div>
        </div>
    </div>

    <script>
        async function analyzeWebsite() {
            const urlInput = document.getElementById('url-input');
            const analyzeBtn = document.getElementById('analyze-btn');
            const errorDiv = document.getElementById('error');
            const loadingDiv = document.getElementById('loading');
            const resultsDiv = document.getElementById('results');
            const scoresGrid = document.getElementById('scores-grid');

            // Reset UI
            errorDiv.style.display = 'none';
            resultsDiv.style.display = 'none';
            loadingDiv.style.display = 'none';

            // Validate URL
            if (!urlInput.value) {
                errorDiv.textContent = 'Please enter a URL';
                errorDiv.style.display = 'block';
                return;
            }

            try {
                new URL(urlInput.value);
            } catch {
                errorDiv.textContent = 'Please enter a valid URL (including http:// or https://)';
                errorDiv.style.display = 'block';
                return;
            }

            try {
                // Show loading state
                loadingDiv.style.display = 'block';
                analyzeBtn.disabled = true;

                const response = await fetch('http://localhost:8080/analyze', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ url: urlInput.value }),
                });

                if (!response.ok) {
                    throw new Error('Failed to analyze website');
                }

                const data = await response.json();
                
                // Update total score
                document.querySelector('.total-score').textContent = `${data.total_score}/10`;

                // Update individual scores
                scoresGrid.innerHTML = '';
                Object.entries(data.scores).forEach(([category, score]) => {
                    const scoreClass = score >= 1.5 ? 'good' : score >= 1 ? 'average' : 'poor';
                    scoresGrid.innerHTML += `
                        <div class="score-item">
                            <span class="category">${category}</span>
                            <span class="score ${scoreClass}">${score}/2</span>
                        </div>
                    `;
                });

                // Show results
                resultsDiv.style.display = 'block';

            } catch (error) {
                errorDiv.textContent = error.message;
                errorDiv.style.display = 'block';
            } finally {
                loadingDiv.style.display = 'none';
                analyzeBtn.disabled = false;
            }
        }
    </script>
</body>
</html>
