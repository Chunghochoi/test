import express from "express";
import https from "https";
import { HttpsProxyAgent } from "https-proxy-agent";

const app = express();
const port = process.env.PORT || 3000;

const targetHost = process.env.TARGET_HOST;
const targetIp = process.env.TARGET_IP;
const targetPath = process.env.TARGET_PATH || "/";

function getProxyUrls() {
  const raw = process.env.PROXY_URLS || "";
  return raw
    .split(",")
    .map((value) => value.trim())
    .filter((value) => value.length > 0);
}

function pickProxy() {
  const proxyUrls = getProxyUrls();
  if (proxyUrls.length === 0) {
    return null;
  }
  const index = Math.floor(Math.random() * proxyUrls.length);
  return proxyUrls[index];
}

function validateConfig() {
  const errors = [];
  if (!targetHost) {
    errors.push("TARGET_HOST is required");
  }
  if (!targetIp) {
    errors.push("TARGET_IP is required");
  }
  if (getProxyUrls().length === 0) {
    errors.push("PROXY_URLS must include at least one proxy");
  }
  return errors;
}

app.get("/health", (_req, res) => {
  const errors = validateConfig();
  if (errors.length > 0) {
    return res.status(500).json({
      status: "error",
      errors,
    });
  }

  return res.json({
    status: "ok",
    proxies: getProxyUrls().length,
    targetHost,
    targetIp,
  });
});

app.get("/fetch", (req, res) => {
  const errors = validateConfig();
  if (errors.length > 0) {
    return res.status(500).json({
      status: "error",
      errors,
    });
  }

  const proxyUrl = pickProxy();
  const path = req.query.path ? String(req.query.path) : targetPath;
  const agent = new HttpsProxyAgent(proxyUrl);

  const request = https.request(
    {
      host: targetIp,
      path,
      method: "GET",
      agent,
      servername: targetHost,
      headers: {
        Host: targetHost,
      },
    },
    (response) => {
      res.status(response.statusCode || 200);
      response.pipe(res);
    }
  );

  request.on("error", (error) => {
    res.status(502).json({
      status: "error",
      message: "Upstream request failed",
      error: error.message,
      proxyUrl,
    });
  });

  request.end();
});

app.listen(port, () => {
  console.log(`Proxy service listening on port ${port}`);
});
