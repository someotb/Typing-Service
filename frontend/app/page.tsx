"use client";

import { useState, useEffect } from "react";
import styles from "./page.module.css";

export default function TypingTest() {
  const [text, setText] = useState("");
  const [input, setInput] = useState("");
  const [timeLeft, setTimeLeft] = useState(30);
  const [isActive, setIsActive] = useState(false);
  const [error, setError] = useState("");
  const [accuracy, setAccuracy] = useState(0);

  // Убираем логику темы, просто включаем тёмную тему при загрузке
  useEffect(() => {
    document.documentElement.classList.add("dark");
    localStorage.setItem("theme", "dark"); // если хочешь, чтобы всегда была тёмная
  }, []);

  // Таймер
  useEffect(() => {
    if (!isActive || timeLeft <= 0) return;

    const timer = setInterval(() => {
      setTimeLeft((prev) => {
        if (prev <= 1) {
          clearInterval(timer);
          setIsActive(false);
          return 0;
        }
        return prev - 1;
      });
    }, 1000);

    return () => clearInterval(timer);
  }, [isActive]);

  // Подсчёт точности
  useEffect(() => {
    if (text && input) {
      let correct = 0;
      for (let i = 0; i < input.length; i++) {
        if (input[i] === text[i]) {
          correct++;
        }
      }
      setAccuracy((correct / text.length) * 100 || 0);
    } else {
      setAccuracy(0);
    }
  }, [input, text]);

  const startTest = async () => {
    try {
      const response = await fetch("/api/typing");
      const data = await response.json();

      if (data.error) {
        setError(data.error);
        return;
      }

      setText(data.text);
      setInput("");
      setTimeLeft(30);
      setIsActive(true);
      setError("");
      setAccuracy(0);
    } catch (err) {
      setError("Ошибка загрузки текста");
    }
  };

  return (
    <div className={styles.container}>
      <div className={styles.card}>
        <h1 className={styles.title}>Напечатай текст за 30 секунд!</h1>

        {error && <div className={styles.error}>{error}</div>}

        <div className={styles.textArea}>
          <p className={styles.textDisplay}>
            {text || 'Нажми "Начать", чтобы получить текст'}
          </p>
        </div>

        <textarea
          value={input}
          onChange={(e) => setInput(e.target.value)}
          disabled={!isActive}
          placeholder="Печатай здесь..."
          className={styles.textInput}
        />

        <div className="flex justify-between items-center">
          <div className={styles.timer}>{timeLeft}с</div>
          <div className={styles.accuracy}>
            Точность:{" "}
            <span className={styles.accuracyValue}>{accuracy.toFixed(2)}%</span>
          </div>
        </div>

        <button
          onClick={startTest}
          disabled={isActive}
          className={styles.button}
        >
          {isActive ? "Тест активен..." : "Начать тест"}
        </button>
      </div>
    </div>
  );
}
