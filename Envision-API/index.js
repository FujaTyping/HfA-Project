const express = require("express");
const axios = require("axios");
require("dotenv").config();

const config = require("./config.json");
const { version } = require("./package.json");
const app = express();
const port = config.port;
const key = process.env.key;

app.get("/version", (req, res) => {
  res.send(version);
});

app.get("/medivise", (req, res) => {
  const PromptMessage = req.query.prompt;
  const AccessPermission = req.query.source;
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
      temperature: 0.6,
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
        Authorization: `Bearer ${key}`,
      },
      data: MedivisePrompt,
    };
    axios
      .request(MediviseConfig)
      .then(async (response) => {
        const Data = response.data;
        const MediviseResponse = Data.choices[0].message.content;
        res.send(MediviseResponse);
      })
      .catch(async (error) => {
        res.send(`Can't comunicate with Medivise (${error})`);
      });
  } else {
    res.status(400).send("Please provide a query - 400");
  }
});

app.use((req, res, next) => {
  res.status(404).send("There is no API here - 404");
});

app.listen(port, () => {
  console.log(`Envision API is running on port : ${port}`);
});
