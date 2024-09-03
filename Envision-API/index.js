const express = require("express");
const axios = require("axios");
const { GoogleGenerativeAI } = require("@google/generative-ai");
require("dotenv").config();

const config = require("./config.json");
const { version, versioncode } = require("./package.json");
const app = express();
const port = config.port;
const openkey = process.env.openkey;
const minikey = process.env.minikey;

const GeminiAI = new GoogleGenerativeAI(minikey);
const GeminiModel = GeminiAI.getGenerativeModel({
  model: "gemini-1.5-flash",
  generationConfig: {
    maxOutputTokens: 80,
    temperature: 0.8,
  },
});

app.use("/favicon.ico", express.static("assets/BetterEnvision.png"));

app.get("/version", (req, res) => {
  res.send(`${version} ${versioncode}`);
});

app.get("/medivise", async (req, res) => {
  const PromptMessage = req.query.prompt;
  const AccessPermission = req.query.source;
  const ModelSelection = req.query.model;
  if (PromptMessage && AccessPermission == "me.siraphop.SmartEnvision") {
    const MedivisePrompt = JSON.stringify({
      model: `typhoon-v1.5-instruct`,
      messages: [
        {
          role: "system",
          content: `You're Medivise is a smart AI healthcare assistant offering personalized medical advice and support`,
        },
        {
          role: "user",
          content: `${PromptMessage}`,
        },
      ],
      max_tokens: 90,
      temperature: 0.7,
      top_p: 1,
      //"repetition_penalty": 1.1,
      stream: false,
    });
    const MediviseConfig = {
      method: "post",
      maxBodyLength: Infinity,
      url: "https://api.opentyphoon.ai/v1/chat/completions",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${openkey}`,
      },
      data: MedivisePrompt,
    };
    if (ModelSelection == "open-medivise") {
      axios
        .request(MediviseConfig)
        .then(async (response) => {
          const Data = response.data;
          const MediviseResponse = Data.choices[0].message.content;
          res.send(MediviseResponse);
        })
        .catch(async (error) => {
          res
            .status(400)
            .send(`Can't comunicate with Open-Medivise (${error})`);
        });
    } else if (ModelSelection == "mini-medivise") {
      try {
        const MiniChat = GeminiModel.startChat({
          history: [
            {
              role: "user",
              parts: [
                {
                  text: "I am Medivise is a smart AI healthcare assistant offering personalized medical advice and support",
                },
              ],
            },
          ],
        });
        //const Data = await GeminiModel.generateContent(PromptMessage);
        //const MiniResponse = Data.response.candidates[0].content.parts[0].text;
        const MiniResponse = await MiniChat.sendMessage(`${PromptMessage}}`);
        res.send(MiniResponse.response.text());
      } catch (e) {
        res.status(400).send(`Can't comunicate with Mini-Medivise (${e})`);
      }
    } else {
      res.status(400).send("Use the correct model (400)");
    }
  } else {
    res.status(400).send("Please provide a query (400)");
  }
});

app.use((req, res, next) => {
  res.status(404).send("There is no API here (404)");
});

app.listen(port, () => {
  console.log(`Envision API is running on port : ${port}`);
});
