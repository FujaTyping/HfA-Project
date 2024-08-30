const express = require("express");
const axios = require("axios");
require("dotenv").config();

const config = require("./config.json");
const app = express();
const port = config.port;
const key = process.env.key;

app.get("/Medivise", (req, res) => {
  const PromptMessage = req.query.prompt;
  const AccessPermission = req.query.source;
  if (PromptMessage && AccessPermission == "me.siraphop.SmartEnvision") {
    const MedivisePrompt = JSON.stringify({
      model: `typhoon-v1.5-instruct`,
      messages: [
        {
          role: "system",
          content: `You're Medivise-Ai is a smart AI healthcare assistant offering personalized medical advice and support and only reponse in Thai`,
        },
        {
          role: "user",
          content: `${PromptMessage}`,
        },
      ],
      max_tokens: 100,
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
        res.send("Can't comunicate with Medivise-Ai");
      });
  } else {
    res
      .status(400)
      .send(
        "Please provide a query & Source of request (Can be use in SmartEnvision only)",
      );
  }
});

app.use((req, res, next) => {
  res.status(404).send("No API that you looking for");
});

app.listen(port, () => {
  console.log(`Medivise API is running on port : ${port}`);
});
