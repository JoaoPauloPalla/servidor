"use client";

import "./globals.css";
import { Box, ThemeProvider } from "@mui/material";
import { lightTheme, darkTheme } from "@/app/themes/theme";
import { useState } from "react";

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  const [theme, setTheme] = useState(lightTheme);
  const toggleTheme = () => {
    setTheme(theme === lightTheme ? darkTheme : lightTheme);
  };

  return (
    <html lang="en">
      <body>
        <ThemeProvider theme={theme}>
          <button onClick={toggleTheme}>Toggle theme</button>
          <Box>{children}</Box>
        </ThemeProvider>
      </body>
    </html>
  );
}
