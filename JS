const express = require('express');
const cors = require('cors');
const axios = require('axios');
const cheerio = require('cheerio');

const app = express();

// Enable CORS properly
app.use(cors());
app.use(express.json());

app.post('/analyze', async (req, res) => {
    try {
        const { url } = req.body;
        
        if (!url) {
            return res.status(400).json({ error: 'URL is required' });
        }

        // Fetch the website content
        const response = await axios.get(url, {
            timeout: 10000,
            headers: {
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
            }
        });

        const $ = cheerio.load(response.data);

        // Scoring logic
        let scores = {
            'Performance': 0,
            'SEO': 0,
            'Content': 0,
            'Mobile': 0,
            'Security': url.startsWith('https') ? 2 : 0
        };

        // Performance (example: check for inline styles)
        scores.Performance = $('style').length > 0 ? 1 : 2;

        // SEO (example: check for meta description and title tag)
        scores.SEO = ($('meta[name="description"]').attr('content') ? 1 : 0) +
                     ($('title').text() ? 1 : 0);

        // Content (example: check if there are images with alt attributes)
        scores.Content = $('img[alt]').length > 0 ? 2 : 1;

        // Mobile (example: check viewport meta tag for responsiveness)
        scores.Mobile = $('meta[name="viewport"]').attr('content') ? 2 : 0;

        const total_score = Object.values(scores).reduce((a, b) => a + b, 0);

        res.json({
            total_score,
            scores
        });

    } catch (error) {
        console.error('Error:', error.message);
        res.status(500).json({ error: 'Failed to analyze website' });
    }
});

// Test endpoint
app.get('/test', (req, res) => {
    res.json({ status: 'Server is running' });
});

const PORT = 8080;
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
