/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:10:26 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/11 14:44:49 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

//resize la texture pour qu'elle correspond a wall size
//refaire un algo raycasting mais qui detecte cette fois les 2
//quand un rayon arrive sur un 2 > creer le plan du sprite perpendiculaire 
//a l'angle de base de la camera (donc creer un segment de longueur 1 avec point xa,ya et xb,yb)
//une fois ce segment creer, verifier si notre rayon touche ce segment
//si oui regarder quelle portion il touche pour savoir quelle portion dessiner
//si non rien il continue
//garder a l'esprit que le rayon doit continuer meme s'il touche un sprite > il doit
//ensuite toucher les autres derriere jusqu'a ce qu'il touche un mur.
//il faut donc save au fur et a mesure les sprites que l'on touche, le type de sprite
//et a quelle hauteur on doit le dessiner